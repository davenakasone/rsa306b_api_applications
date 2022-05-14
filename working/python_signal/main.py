"""
    https://colab.research.google.com/github/misbahsy/APMonitor-do/blob/master/DeepLearning.ipynb#scrollTo=4esWzacmK5b5
    need CUDA
    this is too slow, it can't keep up with 112e6 samples per second
"""

# use the raw ADC files for training and test
# 1. Data Export with Numpy / Import with Pandas
import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import *
import matplotlib.pyplot as plt  

data = pd.read_csv('/content/atrain_data.csv')
mx = data[data.columns[0]].to_numpy()
xx = mx.tolist()
my = data[data.columns[1]].to_numpy()
yy = my.tolist()
# generate training data
x = np.array(xx)
y = np.array(yy)
# save training data to file
data = np.vstack((x,y)).T
np.savetxt('train_data.csv',data,header='x,y',comments='',delimiter=',')

data = pd.read_csv('/content/atest_data.csv')
mx = data[data.columns[0]].to_numpy()
xx = mx.tolist()
my = data[data.columns[1]].to_numpy()
yy = my.tolist()
# generate test data
x = np.array(xx)
y = np.array(yy)
# save test data to file
data = np.vstack((x,y)).T
np.savetxt('test_data.csv',data,header='x,y',comments='',delimiter=',')




























































############################################################################################
import numpy as np
import pandas as pd
import csv
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import *
import matplotlib.pyplot as plt  

data = pd.read_csv('/content/strain_data.csv')
mx = data[data.columns[0]].to_numpy()
xx = mx.tolist()
my = data[data.columns[1]].to_numpy()
yy = my.tolist()
arr = [xx, yy]
dataa = np.vstack((xx,yy)).T
np.savetxt('/content/train_dataa.csv', arr, header='x,y', comments='', delimiter=',')
print(data.describe())

data = pd.read_csv('/content/stest_data.csv')
mx = data[data.columns[0]].to_numpy()
xx = mx.tolist()
my = data[data.columns[1]].to_numpy()
yy = my.tolist()
arr = [xx, yy]
dataa = np.vstack((xx,yy)).T
np.savetxt('/content/test_dataa.csv', arr, header='x,y', comments='', delimiter=',')
print(data.describe())


# 1. Data Export with Numpy / Import with Pandas
import numpy as np
import pandas as pd
import csv
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import *
import matplotlib.pyplot as plt  

header_list = ['x', 'y']
#data = pd.read_csv('train_data.csv', names=header_list)
data = pd.read_csv('strain_data.csv', names=header_list)
xx = list(data.x)
yy = list(data.y)
dataa = np.vstack((xx,yy)).T
np.savetxt('train_dataa.csv', data,header='x,y', comments='', delimiter=',')

#data = pd.read_csv('test_data.csv')
data = pd.read_csv('strain_data.csv', names=header_list)
xx = list(data.x)
yy = list(data.y)
dataa = np.vstack((xx,yy)).T
np.savetxt('test_dataa.csv', data,header='x,y', comments='', delimiter=',')

'''
# generate training data
x = np.linspace(0.0,2*np.pi,20)
y = np.sin(x)
# save training data to file
data = np.vstack((x,y)).T
np.savetxt('train_data.csv',data,header='x,y',comments='',delimiter=',')

# generate test data
x = np.linspace(0.0,2*np.pi,100)
y = np.sin(x)
# save test data to file
data = np.vstack((x,y)).T
np.savetxt('test_data.csv',data,header='x,y',comments='',delimiter=',')
'''


# 2. Data Scaling with scikit-learn
# load training and test data with pandas
train_df = pd.read_csv('train_dataa.csv')
test_df = pd.read_csv('test_dataa.csv')

# scale values to 0 to 1 for the ANN to work well
s = MinMaxScaler(feature_range=(0,1))

# scale training and test data
sc_train = s.fit_transform(train_df)
sc_test = s.transform(test_df)

# print scaling adjustments
print('Scalar multipliers')
print(s.scale_)
print('Scalar minimum')
print(s.min_)

# convert scaled values back to dataframe
sc_train_df = pd.DataFrame(sc_train, columns=train_df.columns.values)
sc_test_df = pd.DataFrame(sc_test, columns=test_df.columns.values)

# save scaled values to CSV files
sc_train_df.to_csv('train_scaled.csv', index=False)
sc_test_df.to_csv('test_scaled.csv', index=False)

"""
# load training and test data with pandas
train_df = pd.read_csv('train_data.csv')
test_df = pd.read_csv('test_data.csv')

# scale values to 0 to 1 for the ANN to work well
s = MinMaxScaler(feature_range=(0,1))

# scale training and test data
sc_train = s.fit_transform(train_df)
sc_test = s.transform(test_df)

# print scaling adjustments
print('Scalar multipliers')
print(s.scale_)
print('Scalar minimum')
print(s.min_)

# convert scaled values back to dataframe
sc_train_df = pd.DataFrame(sc_train, columns=train_df.columns.values)
sc_test_df = pd.DataFrame(sc_test, columns=test_df.columns.values)

# save scaled values to CSV files
sc_train_df.to_csv('train_scaled.csv', index=False)
sc_test_df.to_csv('test_scaled.csv', index=False)
"""


# 3. Model Build and Train with Keras
# create neural network model
model = Sequential()
model.add(Dense(1, input_dim=1, activation='linear'))
model.add(Dense(2, activation='linear'))
model.add(Dense(2, activation='tanh'))
model.add(Dense(2, activation='linear'))
model.add(Dense(1, activation='linear'))
model.compile(loss="mean_squared_error", optimizer="adam")

# load training data
train_df = pd.read_csv("train_scaled.csv")
X1 = train_df.drop('y', axis=1).values
Y1 = train_df[['y']].values

# train the model
model.fit(X1,Y1,epochs=50,verbose=0,shuffle=True)

# Save the model to hard drive
model.save('model.h5')


# 4. Model Validation with Keras
from keras.models import load_model
# Load the model from hard drive
#model.load('model.h5')
model = load_model('model.h5')

# load test data
test_df = pd.read_csv("test_scaled.csv")
X2 = train_df.drop('y', axis=1).values
Y2 = train_df[['y']].values

# test the model
mse = model.evaluate(X2,Y2, verbose=1)

print('Mean Squared Error: ', mse)


# 5. Model Predictions with Keras






























import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import *
import matplotlib.pyplot as plt  

# generate training data
#x = np.linspace(0.0,2*np.pi,20)
#y = np.sin(x)
# save training data to file
#data = np.vstack((x,y)).T
#np.savetxt('train_data.csv',data,header='x,y',comments='',delimiter=',')

data = pd.read_csv('train_data.csv')
data.columns = ["x", "y"]
xx = list(data.x)
yy = list(data.y)
dataa = np.vstack((xx,yy)).T
np.savetxt('train_dataa.csv',data,header='x,y',comments='',delimiter=',')

# generate test data
#x = np.linspace(0.0,2*np.pi,100)
#y = np.sin(x)
# save test data to file
#data = np.vstack((x,y)).T
#np.savetxt('test_data.csv',data,header='x,y',comments='',delimiter=',')

data = pd.read_csv('test_data.csv')
data.columns = ["x", "y"]
xx = list(data.x)
yy = list(data.y)
dataa = np.vstack((xx,yy)).T
np.savetxt('test_dataa.csv',data,header='x,y',comments='',delimiter=',')





# load training and test data with pandas
train_df = pd.read_csv('train_dataa.csv')
test_df = pd.read_csv('test_dataa.csv')

# scale values to 0 to 1 for the ANN to work well
s = MinMaxScaler(feature_range=(0,1))

# scale training and test data
sc_train = s.fit_transform(train_df)
sc_test = s.transform(test_df)

# print scaling adjustments
print('Scalar multipliers')
print(s.scale_)
print('Scalar minimum')
print(s.min_)

# convert scaled values back to dataframe
sc_train_df = pd.DataFrame(sc_train, columns=train_df.columns.values)
sc_test_df = pd.DataFrame(sc_test, columns=test_df.columns.values)

# save scaled values to CSV files
sc_train_df.to_csv('train_scaled.csv', index=False)
sc_test_df.to_csv('test_scaled.csv', index=False)







# create neural network model
model = Sequential()
model.add(Dense(1, input_dim=1, activation='linear'))
model.add(Dense(2, activation='linear'))
model.add(Dense(2, activation='tanh'))
model.add(Dense(2, activation='linear'))
model.add(Dense(1, activation='linear'))
model.compile(loss="mean_squared_error", optimizer="adam")

# load training data
train_df = pd.read_csv("train_scaled.csv")
X1 = train_df.drop('y', axis=1).values
Y1 = train_df[['y']].values

# train the model
model.fit(X1,Y1,epochs=900,verbose=0,shuffle=True)

# Save the model to hard drive
#model.save('model.h5')


# Load the model from hard drive
#model.load('model.h5')

# load test data
test_df = pd.read_csv("test_scaled.csv")
X2 = test_df.drop('y', axis=1).values
Y2 = test_df[['y']].values

# test the model
mse = model.evaluate(X2,Y2, verbose=1)

print('Mean Squared Error: ', mse)


# generate prediction data
#x = np.linspace(-2*np.pi,4*np.pi,100)
#y = np.sin(x)
dat = pd.read_csv('valid_data.csv')
dat.columns = ["x", "y"]
xx = np.array(list(dat.x))
yy = np.array(list(dat.y))

# scale input
X3 = xx*s.scale_[0]+s.min_[0]
# predict
Y3P = model.predict(X3)
# unscale output
yp = (Y3P-s.min_[1])/s.scale_[1]

plt.figure()
plt.plot((X1-s.min_[0])/s.scale_[0], \
                 (Y1-s.min_[1])/s.scale_[1], \
                 'bo',label='train')
plt.plot(xx,yy,'r-',label='actual')
plt.plot(xx,yp,'k--',label='predict')
plt.legend(loc='best')
plt.savefig('results.png')
plt.show()
