from django.shortcuts import render
from django.shortcuts import redirect, get_object_or_404
from django.http import HttpResponse, Http404, FileResponse
from .models import User, Course, Lession, Practice, Score, LessionScore
from django.http import JsonResponse
from django.utils import timezone
from .handleFile import handle_uploaded_file
import random

def index(request):
  return HttpResponse("Hello, world. You're at the polls index.")

def signin(request):

  if request.method == "POST":
    try:
      user = User.objects.get(email= request.POST["email"], password=request.POST["password"])
    except User.DoesNotExist:
      return render(request, "kidapp/index.html",{"warning": "Email or password was incorrect!", "title":"Login"})

    if request.session.has_key("email"):
      del request.session['email']

    request.session['email'] = user.email
    request.session.set_expiry(1800)
    return redirect("/kidapp/courses")

  elif request.method == "GET":
    return render(request, "kidapp/index.html",{"title" : "Login"})

def signout(request):

  try:
    del request.session["email"]
  except:
    pass
  return redirect('/kidapp/signin')

def signup(request):

  if request.method == "POST":   
    email = request.POST["email"]
    password = request.POST["password"]
    repassword = request.POST["repassword"]

    try:
      user = User.objects.get(email= request.POST["email"])
      return render(request, "kidapp/logup.html" , {"error" : "Email was existed" , "title": "Sign-up"})
    except User.DoesNotExist:  
      if len(email) and len(password) and password == repassword:
        user = User(username=email.split("@")[0], password=password, email=email,level=0,phone_number='')
        user.save()
        
        request.session["email"] = user.email
        request.session.set_expiry(1800)
        return redirect('/kidapp/courses')
      else:
        return render(request, "kidapp/logup.html" , { "error" : "Email or password was wrong"})
  else:
    return render(request, "kidapp/logup.html", { "title": "Sign-up"})

def get_List_Course(request):
  
  if "email" in request.session:
    try:
      user = User.objects.get(email=request.session["email"])
    except User.DoesNotExist:
      raise Http404("User does not exist")
    try:
      courses = Course.objects.all()
    except Course.DoesNotExist:
      raise Http404("Course does not exist")
    return render(request, "kidapp/courses.html", {"courses" : courses , "title" : "Courses", "userinfo" : user})
  return redirect("/kidapp/signin")

def get_List_Lession(request, course_id):

  # email = request.session["email"]
  # user = User.objects.get(email=email)
  if "email" in request.session:
    try:
      user = User.objects.get(email=request.session["email"])
    except User.DoesNotExist:
      raise Http404("User does not exist")
    course = get_object_or_404(Course, pk=course_id)

    lessions = [] 
    for lession in course.lession_set.all():
      try:
        lessionscore = LessionScore.objects.get(user=user, lession=lession)
        lessions.append([lession, True])
      except LessionScore.DoesNotExist:
        lessions.append([lession, False])
    
    return render(request, 'kidapp/lessions.html', {'lessions': lessions, "title": "Lessions" , "userinfo" : user })
    # return JsonResponse({"lessions": str(lessions), "title": "Title"})
  return redirect("/kidapp/signin")

def get_Lession_Detail(request, lession_id):
  if "email" in request.session:
    try:
      user = User.objects.get(email=request.session["email"])
    except User.DoesNotExist:
      raise Http404("User does not exist")
    lession = Lession.objects.all().last()
    if lession_id > 1 and lession_id < lession.id:  
      try:
        lession_current = Lession.objects.get(pk=lession_id-1)
        lession_score = LessionScore.objects.get(lession=lession_current)
        if lession_score.score.score == 0:
          return render(request, 'kidapp/detail.html', {'lession': lession_current , "title" : "Lession" , "warning": "You have to finish this lession before move on another lession"})
      except Exception:
        return redirect("/kidapp/detail/" + str(lession_id-1))
    elif lession_id > lession.id:
      return redirect("/kidapp/courses")
    lession = get_object_or_404(Lession, pk=lession_id)

    # count sum score
    scores = LessionScore.objects.filter(user=user, lession=lession)
    sumscore = 0
    for score in scores:
      sumscore += score.score.score
      

    return render(request, 'kidapp/detail.html', {'lession': lession , "title" : "Lession", "userinfo": user, "sumscore" : sumscore})
  return redirect("/kidapp/signin")

def get_List_Practice(request):

  try:
    practices = Practice.objects.all()
  except Practice.DoesNotExist:
    raise Http404("Question does not exist")
  return render(request, "polls/courses.html", {"practices" : practices })


def predict_Number(request):

  if request.method == 'POST':
    return HttpResponse(request.POST["image"])
  else:
    return render(request, "kidapp/home.html", {"username" : "no file"})

def ajax(request):

  if request.method == "POST":
    result = handle_uploaded_file(request.POST["image"])
    # get lession
    lession_id = request.POST["lession"]
    lession = get_object_or_404(Lession, pk=lession_id)
    
    # get user
    email = request.session["email"]
    user = get_object_or_404(User, email = email)
    
    # create score
    if result == lession.right_answer:

      try:
        lession_score = LessionScore.objects.get(lession=lession, user=user)

        if lession_score.score.score != lession.max_score:
          lession_score.score.score = lession.max_score
          lession_score.save()

      except LessionScore.DoesNotExist:

        score = Score(score= lession.max_score)
        score.save()
        lession_score = LessionScore(score=score, lession=lession, user=user)
        lession_score.save()
      random_answer = "/kidapp/audio/good-" + str(random.randint(0, 3)) + ".mp3" 
      return JsonResponse({'result': random_answer, "predict" : str(result) })

    else:
      random_answer = "/kidapp/audio/bad-" + str(random.randint(0, 3)) + ".mp3" 
      return JsonResponse({'result': "/kidapp/audio/bad.mp3", "predict" :str(result) })


def get_audio(request, name):
  music = open('media/sounds/'+ name, 'rb')
  response = FileResponse(music)
  return response
  
def user(request, user_id):
  try:
    user = User.objects.get(pk=user_id)
  except User.DoesNotExist:
    pass
  if request.method == "GET":
    return JsonResponse({"user" : user})
    
def certify(request, certify_id):
  return HttpResponse("dasfasd")