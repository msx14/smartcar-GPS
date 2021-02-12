import argparse
import numpy as np
import keras
from keras import backend as K    # 导入backend
from keras.datasets import cifar10
from keras.models import Sequential, Model, load_model
from keras.layers import Input, Dense, Dropout, Activation, Flatten,ReLU
from keras.layers import DepthwiseConv2D, Conv2D, AveragePooling2D, MaxPooling2D, SeparableConv2D, add
from keras.callbacks import TensorBoard
from keras.layers import BatchNormalization
import os.path as path
import os, sys
from sklearn.model_selection import train_test_split
# import data_convert
# import灰色代表未被调用

def LoadAndSelectData(ad_batch_size):
    # 加载和选择数据，导入npy文件,返回数据集
    # cmd = 'python ./data_convet_seekfree.py -b %d' % ad_batch_size
    # print(cmd)
    # os.popen(cmd + ' > null.log').read()
    train_data = np.load('./ad_train_dat.npy')
    test_data = np.load('./ad_test_dat.npy')
    # np.load和np.save是读写磁盘数组数据的两个主要函数

    train_label = np.load('./pwm_train_label.npy')    # label标签为舵机
    test_label = np.load('./pwm_test_label.npy')
    return train_data, test_data, train_label, test_label

def CreateModelCNN5x3(num_classes = 1, drop = 0.25, isBN = True,ad_batch_size=10):    # num_classes个类别
    model = Sequential()    # 这里的Sequential更准确的应该理解为堆叠，通过堆叠许多层，构建出深度神经网络。
    lstOCs = [30, 12]
    layer = 0   # 层
    model.add(Conv2D(filters = lstOCs[layer], kernel_size=(5, 3),
                padding = 'same', strides = (1,1),
                input_shape = (ad_batch_size,7,1)))    # input_shape参数用于指定输入数据的形状
    if isBN:
        model.add(BatchNormalization())
    model.add(Activation('relu'))   # ReLU激活函数
    
    model.add(Conv2D(filters = lstOCs[layer], kernel_size=(3, 3),
                padding = 'valid', strides = (2,2)))
    if isBN:
        model.add(BatchNormalization())    # 添加BN层
    model.add(Activation('relu'))
    layer += 1
    
    # -----------------
    model.add(Flatten())    # Flatten把多维的输入一维化，常用在从卷积层到全连接层的过渡。
    layer += 1
    # -----------
    if drop > 0:
        model.add(Dropout(drop))
        # 25 % Dropout，已增加随机性，防止过拟合（隐藏层舍弃25%，在前向传播FeedForward时)
    model.add(Dense(180,activation='relu'))
    
    if drop > 0:
        model.add(Dropout(drop))
    model.add(Dense(100,activation='relu'))
    
    if drop > 0:
        model.add(Dropout(drop))
    model.add(Dense(40,activation='relu'))
    model.add(Dense(num_classes))
    if isBN:
        model.add(BatchNormalization())   
    model.summary()    # 使用keras构建深度学习模型，我们会通过model.summary()输出模型各层的参数状况
    sModelName = 'smartcar_ad_cnn5x3_drop_0%d' % (int(drop*100))
    if not isBN:
        sModelName += '_nobn'
    return sModelName, model

def CreateModelDense(num_classes=1, drop=0.25, isBN=True,ad_batch_size=1):
    isBN = 0
    model = Sequential()
    # -----------------
    model.add(Flatten(input_shape = (ad_batch_size,7,1)))    # [[a],[b],[c],[d],[e],[f],[g]]

    model.add(Dense(140))
    model.add(Activation('tanh'))
    if isBN:
        model.add(BatchNormalization())
    if drop > 0:
        model.add(Dropout(drop))
    model.add(Dense(100))
    model.add(Activation('tanh'))
    if isBN:
        model.add(BatchNormalization())
    if drop > 0:
        model.add(Dropout(drop))
    model.add(Dense(40))
    model.add(ReLU(max_value=8))
    if isBN:
        model.add(BatchNormalization())
    model.add(Dense(num_classes))
    if isBN:
        model.add(BatchNormalization())
    model.summary()

    sModelName = 'smartcar_ad_dense_drop_0%d_adSize_%d' % (int(drop * 100),ad_batch_size)
    if not isBN:
        sModelName += '_nobn'
    return sModelName, model

def CreateModelCNN(num_classes = 1, drop = 0.25, isBN = True,ad_batch_size=10):
    model = Sequential()
    lstOCs = [12, 32]
    layer = 0
    model.add(Conv2D(filters = lstOCs[layer], kernel_size=(7, 5),
                padding ='same', strides = (2, 2),
                input_shape = (ad_batch_size, 7, 1)))
    if isBN:
        model.add(BatchNormalization())
    model.add(Activation('tanh'))
    # model.add(MaxPooling2D(pool_size=(2, 2)))
    layer += 1
    
    # model.add(Conv2D(filters = lstOCs[layer], kernel_size=(3, 3),
    #            padding = 'valid', strides = (1,1)))
    # if isBN:
    #    model.add(BatchNormalization())
    # model.add(Activation('relu'))
    # layer += 1
    
    # -----------------
    model.add(Flatten())
    layer += 1
    # -----------

    if drop > 0 :
        model.add(Dropout(drop))
    model.add(Dense(100,activation='tanh'))

    if drop > 0 :
        model.add(Dropout(drop))
    model.add(Dense(50,activation='tanh'))
    # if isBN:
    #    model.add(BatchNormalization())
    # model.add(Activation('sigmoid'))
    model.add(Dense(num_classes))
    if isBN:
        model.add(BatchNormalization())   
    model.summary()
    sModelName = 'smartcar_ad_cnn7x5_drop_0%d_adSize_%d' % (int(drop * 100),ad_batch_size)
    if not isBN:
        sModelName += '_nobn'
    return sModelName, model


if __name__ == '__main__':
    # 只能直接作为脚本运行
    parser = argparse.ArgumentParser()    # 将命令行字符串解析为 python 对象
    parser.add_argument('-r', '--restart', help='restart training', action='store_true')
    # name or flags:是必须的参数，该参数接受选项参数或者是位置参数（一串文件名） help: 使用这个参数描述选项作用 action - 命令行遇到参数时的动作，默认值是 store
    parser.add_argument('-n', '--no_bn', help='restart training', action='store_true')
    parser.add_argument(
        '-d', '--drop', type=float, default=0.25,
        help="""\
        dropout rate, 0 - 1
        """)
    parser.add_argument(
        '-l', '--learn_rate', type=float, default=0.01,
        help="""\
        learning rate
        """)

    parser.add_argument(
        '-m', '--min_learn_rate', type=float, default=0.0007,
        help="""\
        min learning rate, will not decay when learning rate is less than this
        """)

    parser.add_argument(
        '-c', '--decay_ppm', type=float, default=1.5,
        help="""\
        learning rate decay rate, in ppm: 1ppm = 1e-6
        """)
    parser.add_argument(
        '-b', '--batch_size', type=int, default=25,
        help="""\
        batch size
        """)
    parser.add_argument(
        '-ad', '--ad_size', type=int, default=10,
        help="""\
            batch size
            """)
    parser.add_argument(
        '-a', '--arch', type=str, default='dense',
        help="""\
        model architecture: can be 'ds', 'cnn', 'resds', 'cnnfast'
        """)
    # 添加参数，第一个是选项，第二个是数据类型，第三个默认值，第四个是help命令时的说明
 
    args, unparsed = parser.parse_known_args()    # 解析指定部分，多余部分不会报错

    ad_size = args.ad_size
    # Load and select data
    x_train, x_test, y_train, y_test = LoadAndSelectData(ad_size)

    lr = args.learn_rate    # 学习率
    minLR = args.min_learn_rate
    batch_size = args.batch_size    # 一次训练所选取的样本数
    decay = args.decay_ppm / 1e6    # 学习率衰减(learning rate decay)
    histCnt = 20
    lossHist = [1E4] * histCnt
    epocsPerTrain = 1    # epoch使用全部数据对模型进行一次完整的训练
    burstOftCnt = 0
    minLoss = 1E5
    maxAccu = 0    # 每次迭代允许的误差
    opt = keras.optimizers.Adamax(lr, decay)    # 深度学习的一种优化方式
    num_classes = 1

    print(x_train.shape)
    x_train = x_train.reshape(int(x_train.size / ad_size / 7), ad_size, 7, 1)
    x_test = x_test.reshape(int(x_test.size / ad_size/7), ad_size, 7, 1)

    x_train = x_train.astype('int8')
    y_train = y_train.astype('int8')
    x_test = x_train.astype('int8')
    y_test = y_train.astype('int8')
    print('Training data shape:%d' % (min(x_train.flatten())))
    x_train = (x_train / 128).astype('float32')
    x_test = (x_test / 128).astype('float32')
    y_train = ((y_train)/128).astype('float32')
    y_test = ((y_test) / 128).astype('float32')
    print('x_test data shape:%f~%f' %(max(x_train.flatten()),min(x_train.flatten())))
    print('y_test data shape:%f~%f' %(max(y_train),min(y_train)))

    # 判断输入的命令，-a -dense
    if args.arch == '7x5':
        model_name, model = CreateModelCNN(num_classes, args.drop, not args.no_bn,ad_size)
    elif args.arch == '5x3':
        model_name, model = CreateModelCNN5x3(num_classes, args.drop, not args.no_bn,ad_size)
    elif args.arch == 'dense':
        model_name, model = CreateModelDense(num_classes, args.drop, not args.no_bn,ad_size)
    else:
        model_name, model = CreateModelCNN(num_classes, args.drop, not args.no_bn,ad_size)
    # model.summary()

    # 模型训练部分
    model_name, model = CreateModelDense(num_classes, args.drop, not args.no_bn, ad_size)
    print ('Training model ' + model_name)
    # train the model using RMSprop
    logFile = model_name + '_log.txt'
    sSaveModel = '%s.h5' % (model_name)
    sSaveCtx = '%s_ctx.h5' % (model_name)    # 保存临时文件，训练中途意外停止后，重新训练时可以支持断点续练
    if args.restart == False and path.exists(sSaveCtx):
        fd = open(logFile, 'r')
        s = fd.read()
        fd.close()
        lst = s.split('\n')[-2].split(',')
        # split(self, *args, **kwargs),返回字符串中的单词列表，使用 sep 作为分隔符字符串
        for s in lst:
            if s.find('lr=') == 0:
                lr = float(s[3:])
                lr *= (1 - decay) ** (50000 / batch_size)
            if s.find('times=') == 0:
                i = int(s[6:]) - 1 + 1
            if s.find('accu=') == 0:
                maxAccu = float(s[5:])
            if s.find('loss=') == 0:
                minLoss = float(s[5:])                
        print('resume training from ', lst)
        model = load_model(sSaveCtx)
        fd = open(logFile, 'a')
    else:
        fd = open(logFile, 'w')
        s = 'times=%d,loss=%.4f,accu=%.4f,lr=%f,decay=%f' % (0, minLoss, maxAccu, lr, decay)
        fd.write(s + '\n')
        fd.close()
        fd = open(logFile, 'a')
        i = 0
    model.compile(loss='mean_squared_error', optimizer=opt, metrics=['accuracy'])
    # compile：编译，为训练配置模型


    # 训练损失函数，使用mean_squared_error，优化器使用RMSprop
    while i < 120:
        print('Train %d times' % (i + 1))
        hist = model.fit(x_train, y_train, batch_size, epochs=epocsPerTrain, \
            shuffle = True, callbacks=None)  # callbacks=[TensorBoard(log_dir='./log_' + model_name)])
        model.save(sSaveCtx)
        # evaluate
        loss, accuracy = model.evaluate(x_test, y_test)    # accuracy准确率
        # process loss
        loss = int(loss * 10000) / 10000.0
        
        if loss < minLoss:
            minLoss = loss
            maxAccu = accuracy
            print('Saved a better model!')
            model.save(sSaveModel)
            s = 'Saved times=%d,loss=%.4f,accu=%.4f,lr=%f,decay=%f' % (i+1, minLoss, maxAccu,lr, decay)
        else:   
            # save log
            s = 'times=%d,loss=%.4f,accu=%.4f,lr=%f,decay=%f' % (i+1, minLoss, maxAccu,lr, decay)
        # check if it is overfit
        oftCnt = 0
        for k in range(histCnt):
            if loss > lossHist[k]:
                oftCnt += 1
        oftRate = oftCnt / histCnt
        print('overfit rate = %d%%' % int(oftRate * 100))
        if oftCnt / histCnt >= 0.6:
            burstOftCnt += 1
            if burstOftCnt > 3:
                print('Overfit!')
        else:
            burstOftCnt = 0
        s = s + 'overfit rate = %d%%' % int(oftRate * 100)
        
        lossHistPrnCnt = 6
        if lossHistPrnCnt > histCnt:
            lossHistPrnCnt = histCnt
        fd.write(s + '\n')
        print(s, lossHist[:lossHistPrnCnt])    # 打印从目前算起的前6次
        fd.close()
        
        # update loss history
        for k in range(histCnt - 1):
            ndx = histCnt - 1 - k
            lossHist[ndx] = lossHist[ndx - 1]
        lossHist[0] = loss

        fd = open(logFile, 'a')
        lr *= (1 - decay) ** (50000 / batch_size)
        if lr < minLR:
            lr = minLR
        model = load_model(sSaveCtx)
        opt = keras.optimizers.Adamax(lr, decay)
        print('new lr_rate=%f' % (lr))
        model.compile(loss='mean_squared_error', optimizer=opt, metrics=['accuracy'])    # mean_squared_error均方差
        i += 1











