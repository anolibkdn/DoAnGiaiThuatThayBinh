# Generated by Django 2.2.2 on 2019-11-12 03:11

from django.db import migrations, models
import django.db.models.deletion
import kidapp.utils


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Card',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=100)),
                ('cover_image', models.ImageField(blank=True, null=True, upload_to=kidapp.utils.wrapper)),
                ('description', models.CharField(max_length=250)),
                ('date_of_create', models.DateField()),
            ],
        ),
        migrations.CreateModel(
            name='Course',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('topic', models.CharField(max_length=100)),
                ('courses', models.IntegerField(blank=True)),
                ('card', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Card')),
            ],
        ),
        migrations.CreateModel(
            name='Lession',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('level', models.IntegerField(default=0)),
                ('right_answer', models.IntegerField()),
                ('max_score', models.IntegerField(default=100)),
                ('image', models.ImageField(blank=True, null=True, upload_to=kidapp.utils.wrapper)),
                ('sound', models.FileField(blank=True, null=True, upload_to=kidapp.utils.wrapper)),
                ('guide', models.TextField(blank=True)),
                ('card', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Card')),
                ('course', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Course')),
            ],
        ),
        migrations.CreateModel(
            name='Practice',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('practice_scope', models.CharField(max_length=100)),
                ('number_question', models.IntegerField()),
                ('level', models.IntegerField(default=1)),
                ('card', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Card')),
                ('course', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Course')),
            ],
        ),
        migrations.CreateModel(
            name='Question',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('question', models.CharField(max_length=250)),
                ('answer', models.CharField(max_length=250)),
                ('explain', models.CharField(max_length=200)),
                ('level', models.IntegerField()),
                ('practice', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Practice')),
            ],
        ),
        migrations.CreateModel(
            name='Score',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('score', models.IntegerField(default=0)),
                ('date', models.DateField(auto_now=True)),
            ],
        ),
        migrations.CreateModel(
            name='User',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('username', models.CharField(max_length=100)),
                ('password', models.CharField(max_length=50)),
                ('email', models.EmailField(max_length=254, unique=True)),
                ('profile_image', models.ImageField(default='default.png', upload_to=kidapp.utils.wrapper)),
                ('birthday', models.DateField(blank=True, null=True)),
                ('date_of_create', models.DateField(auto_now=True)),
                ('level', models.IntegerField(default=1)),
                ('phone_number', models.CharField(max_length=10)),
            ],
        ),
        migrations.CreateModel(
            name='WriteCase',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('image', models.ImageField(blank=True, null=True, upload_to=kidapp.utils.wrapper)),
                ('sound', models.FileField(blank=True, null=True, upload_to=kidapp.utils.wrapper)),
                ('question', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Question')),
            ],
        ),
        migrations.CreateModel(
            name='QuizCase',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('case', models.CharField(max_length=20)),
                ('question', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Question')),
            ],
        ),
        migrations.CreateModel(
            name='PracticeScore',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('practice', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Practice')),
                ('score', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Score')),
                ('user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kidapp.User')),
            ],
        ),
        migrations.CreateModel(
            name='LessionScore',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('lession', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Lession')),
                ('score', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to='kidapp.Score')),
                ('user', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kidapp.User')),
            ],
        ),
    ]
