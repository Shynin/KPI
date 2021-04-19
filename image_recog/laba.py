import tensorflow as tf
import tensorflow.keras as keras
import tensorflow.keras.backend as K
import numpy as np
import matplotlib.pyplot as plt

tf.enable_eager_execution()
# K.set_image_data_format('channels_first')

# tf.__version__

# K.image_data_format() [B H W C]


def plot_accouracy_training_history(history):
    plt.plot(history.history['acc'])
    plt.title('model accuracy')
    plt.ylabel('accuracy')
    plt.xlabel('epoch')
    plt.legend(['train'], loc='upper left')
    plt.show()

    def plot_accuracy_training_history_with_validation(history):
    plt.plot(history.history['acc'])
    plt.plot(history.history['val_acc'])
    plt.title('model accuracy')
    plt.ylabel('accuracy')
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper left')
    plt.show()

    def plot_loss_training_history(history):
    plt.plot(history.history['loss'])
    plt.title('model loss')
    plt.ylabel('loss')
    plt.xlabel('epoch')
    plt.legend(['train'], loc='upper left')
    plt.show()

    def plot_loss_training_history_with_validation(history):
    plt.plot(history.history['loss'])
    plt.plot(history.history['val_loss'])
    plt.title('model loss')
    plt.ylabel('loss')
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper left')
    plt.show()

    #(x_train, y_train), (x_test, y_test) = keras.datasets.fashion_mnist.load_data()
    # x_test.shape


    # Parameters for our graph; we'll output images in a 4x4 configuration
nrows = 10
ncols = 10

# Index for iterating over images
pic_index = 0

# Set up matplotlib fig, and size it to fit 4x4 pics
fig = plt.gcf()
plt.style.use('grayscale')
fig.set_size_inches(ncols, nrows)

images_to_show_count = nrows * ncols

pic_index += images_to_show_count
next_image_pix = [image for image in x_train[pic_index -
                                             images_to_show_count:pic_index, :, :]]

for i, img in enumerate(next_image_pix):
    # Set up subplot; subplot indices start at 1
    sp = plt.subplot(nrows, ncols, i + 1)
    sp.axis('Off')  # Don't show axes (or gridlines)

    plt.imshow(img)

plt.show()

x_train = x_train / 255.0
x_test = x_test / 255.0
