from django.urls import path, include
from . import views

app_name = "kidapp"
urlpatterns = [
    path('', views.index, name="index"),
    path('signin/', views.signin, name="signin"),
    path('signup/', views.signup, name="signup"),
    path('signout/', views.signout, name="signout"),
    path('courses/', views.get_List_Course, name="courses"),
    path('lessions/<int:course_id>/', views.get_List_Lession, name="lessions"),
    path('detail/<int:lession_id>/', views.get_Lession_Detail, name="detail"),
    path('predict/', views.predict_Number, name="predict"),
    path('ajax/', views.ajax, name="ajax"),
    path('user/<int:user_id>/', views.user, name="user"),
    path('certify/<int:certify_id>/', views.certify, name="certify"),
    path('audio/<name>/', views.get_audio, name="audio"),
]