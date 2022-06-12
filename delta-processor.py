import argparse
import sys


def analyze(f_name,idx):
    cnt={}
    n_inst=0
    with open (f_name) as f:
        for line in f:
            l = line.split(' ')
            if len(l)<3:
                continue
            if idx==1 and len(l[0])!=1:
                continue
            cnt[l[idx]]=cnt.get(l[idx],0)+1
            n_inst+=1
    print(f_name," pc cnt: ",len(cnt)," inst cnt: ", n_inst)
    return cnt

def delta(dict1,dict2):
    cnt ={}
    inst_cnt=0
    for k,v in dict2.items():
        if k not in dict1:
            cnt[k]=dict2[k]
            continue
        if v!=dict1[k]:
            cnt[k]=dict2[k]-dict1[k]
            inst_cnt+=cnt[k]
    return cnt

def analyze_print():
    dict1 = analyze("./output_print_1.txt",1)
    dict2 = analyze("./output_print_2.txt",1)
    return delta(dict1,dict2)


def analyze_spike():
    dict1 = analyze("./output_spike_1.txt",4)
    dict2 = analyze("./output_spike_2.txt",4)
    return delta(dict1,dict2)

dict_print = analyze_print()
dict_spike = analyze_spike()
print(delta(dict_print,dict_spike))