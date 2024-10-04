import silence_tensorflow.auto

import tensorflow as tf
from sklearn.preprocessing import LabelEncoder
import numpy as np
import requests


def predict():
    wifi_address = 'http://192.168.4.22'

    # load data and init encoder
    saved_model = tf.keras.models.load_model('sign_model.h5')
    label_encoder = LabelEncoder()
    y = label_encoder.fit_transform(['fist', 'open', 'thumbup', 'thumbdown', 'point'])


    # get data
    r = requests.get(wifi_address).json().values()
    list = []
    for i in r:
        list.append(float(i))
        
    # make prediction
    prediction = saved_model.predict([list], verbose = 0)

    # Decode prediction
    decoded_prediction = label_encoder.inverse_transform(np.argmax(prediction, axis=1))
    return decoded_prediction


if __name__ == '__main__':
    while(1):
        str = predict()[0] + "     "
        print(str, end = '\r')
