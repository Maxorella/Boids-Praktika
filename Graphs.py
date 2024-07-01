import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.cm as cm
from PIL import Image
import glob
import argparse
import os
import re

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

def natural_sort_key(s, _nsre=re.compile('([0-9]+)')):
    return [int(text) if text.isdigit() else text.lower() for text in re.split(_nsre, s)]

def main(input_dir, output_dir):
    OutFilesList = glob.glob(os.path.join(input_dir, '[0-9]*.txt'))
    OutFilesList.sort(key=natural_sort_key)

    for Filename in OutFilesList:
        with open(Filename, 'r') as file1:
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

            name = os.path.join(output_dir, os.path.splitext(os.path.basename(Filename))[0] + '.jpg')

            if Params['DebugShow']:
                plt.show()

            if Params['SaveRez']:
                plt.savefig(name, dpi=Params['Dpi'])
            plt.close(fig)

    OutFilesList = glob.glob(os.path.join(output_dir, '[0-9]*.jpg'))
    OutFilesList.sort(key=natural_sort_key)
    image_list = [Image.open(file) for file in OutFilesList]
    image_list[0].save(
        os.path.join(output_dir, 'OUT.gif'),
        save_all=True,
        append_images=image_list[1:],
        duration=500,
        loop=0)

if __name__ == "__main__":
    import re
    parser = argparse.ArgumentParser(description="Process and plot data from text files.")
    parser.add_argument('input_dir', type=str, help="Input directory containing text files.")
    parser.add_argument('output_dir', type=str, help="Output directory for saving images.")
    args = parser.parse_args()
    main(args.input_dir, args.output_dir)
