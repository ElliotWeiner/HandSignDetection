import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import tensorflow as tf
from tensorflow.keras import layers, models

# Define your feedforward neural network model
def create_model(input_shape):
    model = models.Sequential([
        layers.Dense(64, activation='relu', input_shape=input_shape),
        layers.Dense(64, activation='relu'),
        layers.Dense(5, activation='softmax')  # Assuming 5 classes for signs
    ])
    return model

if __name__ == '__main__':
    # Load dataset from CSV file
    dataset = pd.read_csv('data.csv')

    X = dataset.drop(columns=['sign'])  # Features
    y = dataset['sign']  # Labels
    
    print("loaded dataset")

    # Encode labels if they are not already in numerical format
    label_encoder = LabelEncoder()
    y = label_encoder.fit_transform(y)

    # Split the dataset into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    print("split dataset")

    # Create model
    model = create_model((X_train.shape[1],))

    # Compile model
    model.compile(optimizer='adam',
                loss='sparse_categorical_crossentropy',
                metrics=['accuracy'])

    print("created model")

    # Train model
    history = model.fit(X_train, y_train, epochs=100, batch_size=32, validation_data=(X_test, y_test))


    # Evaluate model
    test_loss, test_acc = model.evaluate(X_test, y_test)
    print('Test accuracy:', test_acc)

    # Save the model
    model.save('sign_model.h5')

