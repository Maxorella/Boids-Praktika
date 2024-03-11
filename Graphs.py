import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.cm as cm
from PIL import Image
import glob

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

OutFilesList = glob.glob('../out/[0-9]*.txt')
OutFilesList.sort(key=lambda name: name)

for Filename in OutFilesList:
    file1 = open(Filename, 'r')
    Lines = file1.readlines()
    x = []
    y = []
    z = []
    xfood = []
    yfood = []
    zfood = []
    NextFood = False

    fig, ax = plt.subplots()

    for poss, line in enumerate(Lines):
        l = line.split()
        if poss == 0:
            xfood.append(float(l[0]))
            yfood.append(float(l[1]))
            zfood.append(0)
            #if Params['NumbersNearPoint']:
            #    plt.annotate(str(round(zfood[-1], 2)), (round(float(l[0]), 2), round(float(l[1]), 2)),
            #                 (round(float(l[0]) + 0.1, 2), round(float(l[1]) + 0.1, 2)), fontsize=Params['AnnotateFontSize'])
            continue

        if len(l) == 4:
            x_center = float(l[0])
            y_center = float(l[1])
            z_center = float(l[2])
            radius = float(l[3])

            norm = plt.Normalize(vmin=0, vmax=Params['MaxHeight'])
            color = cm.RdYlBu(norm(z_center))

            circle = patches.Circle((x_center, y_center), radius, facecolor=color, fill=True, edgecolor='black', linewidth=0.2)
            ax.add_patch(circle)

            if Params['NumbersNearPoint']:
                plt.annotate(str(round(z_center, 2)), (x_center, y_center), (x_center + 0.1, y_center + 0.1),
                             fontsize=Params['AnnotateFontSize'])

            continue

        if len(l) == 1:
            NextFood = True
            continue

        if len(l) == 3:
            x.append(float(l[0]))
            y.append(float(l[1]))
            z.append(float(l[2]))
            if Params['NumbersNearPoint']:
                plt.annotate(str(round(float(l[2]), 2)), (float(l[0]), float(l[1])),
                             (float(l[0]) + 0.1, float(l[1]) + 0.1), fontsize=Params['AnnotateFontSize'])
            continue

        if len(l) == 2:
            xfood.append(float(l[0]))
            yfood.append(float(l[1]))
            zfood.append(0)
            if Params['NumbersNearPoint']:
                plt.annotate(str(round(zfood[-1], 2)), (float(l[0]), float(l[1])),
                             (float(l[0]) + 0.1, float(l[1]) + 0.1), fontsize=Params['AnnotateFontSize'])
            continue

    x1, y1, x2, y2 = Params['LeftBorder'], Params['BottomBorder'], Params['RightBorder'], Params['TopBorder']
    width = x2 - x1
    height = y2 - y1
    rectangle = patches.Rectangle((x1, y1), width, height, linewidth=1, edgecolor='black', facecolor='none')
    ax.add_patch(rectangle)

    plt.xlim(Params['LeftBorder'] - 5, Params['RightBorder'] + 5)
    plt.ylim(Params['BottomBorder'] - 5, Params['TopBorder'] + 5)
    plt.xlabel("Метры")
    plt.ylabel("Метры")

    if Params['ColorPlot']:
        sc = ax.scatter(x, y, c=z, vmin=0, vmax=Params['MaxHeight'], s=Params['DotSize'], cmap=cm.RdYlBu)
        cbar = plt.colorbar(sc, ax=ax)
        cbar.set_label(label="Height", size=20)
    else:
        sc2 = ax.scatter(x, y, 'o', s=Params['DotSize'], color='black')

    sc3 = ax.scatter(x=xfood, y=yfood, s=Params['DotSize'], color='black')

    name = Filename.split('.')[0] + '.jpg'

    if Params['DebugShow']:
        plt.show()

    if Params['SaveRez']:
        plt.savefig(name, dpi=Params['Dpi'])
    plt.close(fig)
OutFilesList = glob.glob('../out/[0-9]*.jpg')
OutFilesList.sort(key=lambda name: name)
image_list = [Image.open(file) for file in OutFilesList]
image_list[0].save(
    '../out/OUT.gif',
    save_all=True,
    append_images=image_list[1:],
    duration=500,
    loop=0)