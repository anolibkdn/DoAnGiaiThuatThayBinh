import os
import base64
from django.core.files.base import ContentFile
import random
import numpy as np

def handle_uploaded_file(f):
    filename = str(random.randint(0, 100000)) + ".png"
    with open('media/dataset/{}'.format(filename), 'wb+') as destination:  
        img = f.replace('data:image/png;base64,','')
        img = base64.b64decode(img)
        destination.write(img)
    return predict(filename)

import cv2 as cv
from sklearn.datasets import load_digits
from sklearn.linear_model import Perceptron
from sklearn.linear_model import LogisticRegression

X, y = load_digits(return_X_y=True)
clf = Perceptron(tol=1e-3, random_state=0)
clf.fit(X, y)
# clf = LogisticRegression(random_state=0, solver='lbfgs', multi_class='multinomial').fit(X, y)

def predict(image):
    size = 8
    img = cv.imread("media/dataset/" + image)
    img = cv.cvtColor(img , cv.COLOR_BGR2GRAY)
    new_img = cv.resize(src=img,dsize=(size,size))
    new_img = new_img.reshape(-1,size*size)
    result = clf.predict(new_img)
    return result[0]