from django.contrib import admin
from .models import User,Card,Course,Lession,Practice,Score,PracticeScore,LessionScore,Question,QuizCase,WriteCase

class LessionInline(admin.TabularInline):
  model = Lession

class CourseAdmin(admin.ModelAdmin):
  inlines = [
    LessionInline,
  ]

class QuestionInline(admin.TabularInline):
  model = Question

class PracticeAdmin(admin.ModelAdmin):
  inlines = [
    QuestionInline,
  ]
# Register your models here.
admin.site.register(User)  
admin.site.register(Card) 
admin.site.register(Course, CourseAdmin) 
admin.site.register(Lession) 
admin.site.register(Practice, PracticeAdmin) 
admin.site.register(Score) 
admin.site.register(PracticeScore) 
admin.site.register(LessionScore) 
admin.site.register(Question) 
admin.site.register(QuizCase) 
admin.site.register(WriteCase) 