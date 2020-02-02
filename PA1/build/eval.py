
import csv
from os import listdir
from os.path import isfile, join

mypath = "/home/xy97/"
onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]
OUTPUT_NAME = "eval_n_"+str(len(onlyfiles))

buff = [[] for i in range(0,20*2)]

# serial_times = []

with open(OUTPUT_NAME+".csv",mode='w') as csv_file:
  for i in range(len(onlyfiles)):
    if "XiaoyuJob.o" in onlyfiles[i]:    
      n = []
      parallel_times = []
      seq_times = []
      with open('/home/xy97/'+onlyfiles[i], 'r') as fd:
        contents = fd.readlines()
        for j in contents:
          lst = j.split('|')
          if "PARALLEL" in j:
            end = lst[1].find(',')
            n_lst = int(lst[1][2:end])
            n.append(n_lst)
            start = lst[2].find(': ')
            end = lst[2].find(' s')
            parallel_times.append(float(lst[2][start+2:end]))
            # Finding out num proc:
            p = int(lst[1][lst[1].find('p=')+2:]) #isolate p
          if "SERIAL" in j:
            n_lst = int(lst[1][2:])
            n.append(n_lst)
            end = lst[2].find(' s')
            start = lst[2].find(': ')
            seq_times.append(float(lst[2][start+2:end]))
            p = 1
        append_lst = seq_times if p==1 else parallel_times
        buff[(p-1)*2+1].extend(append_lst)
        buff[(p-1)*2].extend(n)
        print len(buff[0]), len(parallel_times), len(seq_times), onlyfiles[i]
  writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
  # writer.writerow([i for i in range(0,)])
  # print buff
  # buff[0].sort()
  for i in range(len(buff[0])):
    pack = []
    for j in range(len(buff)):
      try:
        pack.append(buff[j][i])
      except:
        pack.append(0)
    writer.writerow(pack)

# # print n
# # print parallel_times
# # print serial_times
# # speedup = []
# # for i in range(len(n)-1):
#   # speedup.append(serial_times[i]/parallel_times[i])

# with open(OUTPUT_NAME+p+".csv",mode='w') as csv_file:
#   writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
#   for i in range(len(n)-1):
#     writer.writerow([n[i],parallel_times[i]])
#     # writer.writerow([n[i],serial_times[i],parallel_times[i],speedup[i]])