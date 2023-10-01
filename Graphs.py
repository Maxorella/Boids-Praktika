import matplotlib.pyplot as plt
x=[]
y=[]
for i in range(1,34):
    file1 = open(str(i), 'r')
    Lines = file1.readlines()
    x=[]
    y=[]

    for line in Lines:
        l = line.split()
        x.append(float(l[0]))
        y.append(float(l[1]))
    print(x)
    print(y)
    plt.xlim (-40, 40)
    plt.ylim (-40, 40)

    plt.plot(x, y,'o', color='black')
    name = str(i)+'.jpg'
    plt.savefig(name)
    plt.cla()

#   plt.savefig('foo.pdaf',bbox_inches='tight')