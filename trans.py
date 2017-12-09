import sys
input = sys.argv[1]
print input
fo = open(input+'.libsvm','w')
with open(input) as f:
    lines=f.readlines()
    for line in lines:
        line = line.split()
        label = line[-1]
        for i in range(len(line)-2):
            line[i] = ' '+str(i)+':'+line[i+1]
        line = line[:-1]
        #line = [' '++':'+a for a in line[1:-1]]
        fo.write(label+''.join(line)+'\n')
fo.close()

