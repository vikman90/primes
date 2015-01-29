#!/bin/python3

from subprocess import check_output

sentinel = "Tiempo:"
begin = 1000000
end =   50000000

def gettime(args):
    out = str(check_output(args, shell=True))
    return float(out.split("Tiempo: ")[1].split()[0])

def main():
    i = begin
    step = begin

    while i <= end:
    #for i in range(begin, end + 1, step):
        time = gettime("bin/list -nowrite " + str(i))
        print(str(i) + "\t" + str(time).replace('.',','))
        #print(str(time).replace('.',','))
        
        i += step

        if i == step * 10:
            step = i

if __name__ == "__main__":
    main() 
