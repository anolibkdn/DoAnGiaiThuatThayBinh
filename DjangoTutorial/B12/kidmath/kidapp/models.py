from django.db import models
from .utils import UploadToPathAndRename

# User,UserEnrolment,Card,Course,Lession,Practice,Score,PracticeScore,LessionScore,Question,QuizCase,WriteCase
# Create your models here.
class User(models.Model):
  username = models.CharField(max_length=100)
  password = models.CharField(max_length=50)
  email = models.EmailField(unique=True)
  profile_image = models.ImageField(blank=False, default='default.png', upload_to = UploadToPathAndRename('user/'))
  birthday = models.DateField(blank=True, null=True)
  date_of_create = models.DateField(auto_now=True)
  level = models.IntegerField(default=1)
  phone_number = models.CharField(max_length=10)

  def __str__(self):
      return self.email


class Card(models.Model):
  title = models.CharField(max_length=100)
  cover_image = models.ImageField(upload_to=UploadToPathAndRename('card/'), blank=True, null=True)
  description = models.CharField(max_length=250)
  date_of_create = models.DateField(auto_now=False)

  def __str__(self):
    return self.title

class Course(models.Model):
  card =  models.OneToOneField( Card, on_delete = models.CASCADE)
  topic = models.CharField(max_length=100)
  courses = models.IntegerField(blank=True)

  def __str__(self):
    return self.topic

class Lession(models.Model):
  card = models.OneToOneField( Card, on_delete = models.CASCADE)
  course = models.ForeignKey('Course', on_delete=models.CASCADE)
  level = models.IntegerField(default=0)
  right_answer = models.IntegerField()
  max_score = models.IntegerField(default=100)
  image =  models.ImageField(upload_to=UploadToPathAndRename('iwq/'), blank=True, null=True)
  sound =  models.FileField(upload_to=UploadToPathAndRename('sound/'), blank=True, null=True)
  guide = models.TextField(blank=True)

  def __str__(self):
    return self.card.title

class Practice(models.Model):
  card =  models.OneToOneField( Card, on_delete = models.CASCADE)
  practice_scope = models.CharField(max_length=100)
  number_question = models.IntegerField()
  level = models.IntegerField(default=1)
  course = models.OneToOneField( Course, on_delete = models.CASCADE)

class Score(models.Model):
  score = models.IntegerField(default=0)
  date = models.DateField(blank=True, auto_now=True)

  def __str__(self):
    return str(self.score)

class PracticeScore(models.Model):
  score = models.OneToOneField( Score, on_delete = models.CASCADE)
  practice = models.OneToOneField( Practice, on_delete = models.CASCADE)
  user = models.ForeignKey( User , on_delete=models.CASCADE)

  
class LessionScore(models.Model):
  user = models.ForeignKey( User , on_delete=models.CASCADE)
  score = models.OneToOneField( Score, on_delete = models.CASCADE)
  lession = models.ForeignKey( Lession, on_delete = models.CASCADE) 

class Question(models.Model):
  question = models.CharField(max_length=250)
  answer = models.CharField(max_length=250)
  explain = models.CharField(max_length=200)
  level = models.IntegerField()
  practice = models.ForeignKey("Practice", on_delete = models.CASCADE)

class QuizCase(models.Model):
  question = models.ForeignKey("Question" , on_delete = models.CASCADE)
  case = models.CharField(max_length=20)

class WriteCase(models.Model):
  question = models.OneToOneField( Question , on_delete = models.CASCADE)
  image = models.ImageField(upload_to=UploadToPathAndRename('iwq/'), blank=True, null=True)
  sound = models.FileField(upload_to=UploadToPathAndRename('sounds/'), blank=True, null=True)