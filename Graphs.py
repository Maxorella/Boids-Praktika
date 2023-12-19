import matplotlib
import matplotlib.pyplot as plt
import glob
from PIL import Image
from math import  *
from matplotlib import cm  # Add this line

Params = {
    'NumbersNearPoint': True,
    'AnnotateFontSize': 4,
    'ColorPlot': True,
    'LeftBorder': -40,
    'RightBorder': +40,
    'BottomBorder': -40,
    'TopBorder': +40,
    'MaxHeight': +10,
    'DebugShow': False,
    'SaveRez': True,
    'Dpi': 400,
    'DotSize': 5
}
OutFilesList = glob.glob('[0-9]*.txt')
OutFilesList.sort(key=lambda name: int(name.split('.')[0]))
print(OutFilesList)


NextFood=False

for Filename in OutFilesList:
    file1 = open(Filename, 'r')
    Lines = file1.readlines()
    x = []
    y = []
    z = []
    xfood=[]
    yfood=[]
    zfood=[]
    #   ax = plt.subplot()
    #   im = ax.imshow(np.arange(100).reshape((10, 10)))
    for poss,line in enumerate(Lines):
        l = line.split()
        if poss==0:
            xfood.append(float(l[0]))
            yfood.append(float(l[1]))
            zfood.append(0)  # для машины
            if (Params['NumbersNearPoint']):
                plt.annotate(str(round(zfood[-1],2)),  (round(float(l[0]),2) , round(float(l[1]),2)), (round(float(l[0]) + 0.1,2) , round(float(l[1]) + 0.1,2)  ), fontsize=Params['AnnotateFontSize'])
            continue

        if len(l) == 4:
            x_center = float(l[0])
            y_center = float(l[1])
            z_center = float(l[2])
            radius = float(l[3])

            norm = plt.Normalize(vmin=0, vmax=Params['MaxHeight'])
            color = cm.RdYlBu(norm(z_center))

            circle = plt.Circle((x_center, y_center), radius, color=color, fill=True)
            plt.gca().add_patch(circle)

            if Params['NumbersNearPoint']:
                plt.annotate(str(round(z_center, 2)), (x_center, y_center), (x_center + 0.1, y_center + 0.1),
                             fontsize=Params['AnnotateFontSize'])

            continue


        if (len(l)) == 1:
            NextFood = True
            continue


        if (len(l)==3):
            x.append(float(l[0]))
            y.append(float(l[1]))
            z.append(float(l[2]))
            if(Params['NumbersNearPoint']):
                plt.annotate(str(round(float(l[2]),2)), (float(l[0]), float(l[1])), (float(l[0]) + 0.1, float(l[1]) + 0.1), fontsize=Params['AnnotateFontSize'])
            continue

        if (len(l)) == 2:
            xfood.append(float(l[0]))
            yfood.append(float(l[1]))
            zfood.append(0) # пометка для еды TODO можно сделать лучше
            if (Params['NumbersNearPoint']):
                plt.annotate(str(round(zfood[-1],2)), (float(l[0]), float(l[1])), (float(l[0]) + 0.1, float(l[1]) + 0.1), fontsize=Params['AnnotateFontSize'])
            continue


    plt.xlim(Params['LeftBorder'], Params['RightBorder'])
    plt.ylim(Params['BottomBorder'], Params['TopBorder'])
    if (Params['ColorPlot']):
        sc = plt.scatter(x, y, c=z, vmin=0, vmax=Params['MaxHeight'], s=Params['DotSize'], cmap=matplotlib.colormaps['RdYlBu'])
        cbar = plt.colorbar(sc)
        cbar.set_label(label="Height", size=20)
    # plt.plot(x, y, 'o', color=(.9333, .5098, .9333))
    else:
        sc2 = plt.scatter(x, y,'o', s=Params['DotSize'], color='black')
    sc3 = plt.scatter(x=xfood,y=yfood,s=Params['DotSize'],color='black')
    name = Filename.split('.')[0] + '.jpg'
    if (Params['DebugShow']):
        plt.show()
    if (Params['SaveRez']):
        plt.savefig(name, dpi=Params['Dpi'])
    plt.cla()
    plt.clf()

OutFilesList = glob.glob('[0-9]*.jpg')
OutFilesList.sort(key=lambda name: int(name.split('.')[0]))
image_list = [Image.open(file) for file in OutFilesList]
image_list[0].save(
    'OUT.gif',
    save_all=True,
    append_images=image_list[1:], # append rest of the images
    duration=500, # in milliseconds
    loop=0)