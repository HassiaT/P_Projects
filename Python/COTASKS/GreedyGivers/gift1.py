# -*- coding: utf-8 -*-
"""
TASK : gift1
"""

def generate_dico_from_file(filename):
    with open(filename)  as fih:
        content_items = fih.read().replace('\n', '*').replace('\r\n', '*').split('*')
        dict_of_lines = {counter:(x, x.count(' ')) for counter,x in enumerate(content_items,1)}
        fih.close()
    return dict_of_lines

def initialize_money(dict_lines):
        NP = int(dict_lines[1][0]) 
        if( NP>=2 and NP <= 10):
            list_money = [x for x in [0]*NP]
            list_members = [dict_lines[i][0] for i in range(2, NP+2)]
            dict_members = dict(zip(list_members, list_money))
        return dict_members


def write_output_file(out_filename, final_dict):
    count=0
    if( final_dict):
        with open(out_filename, "w") as fih:
            for (k,v) in final_dict.items():
                new_item = "".join([k, ' ', str(v), '\n'])
                count +=1
                fih.write(new_item)
            fih.close()  


def compute_sum_money(dict_of_lines, dict_of_members):
    indices_partition = [k for (k,v) in dict_of_lines.items() if v[1] == 1]
    split_lines = [dict_of_lines[k][0] for k in indices_partition]
    givers = [dict_of_lines[k-1][0] for k in indices_partition]
    figures = [split_lines[i].split(' ') for i in range(0, len(split_lines))]
    money_ind = [(int(l[0]), int(l[1])) for l in figures]
    auxiliary = [(k // g, k%g) if g> 0 else (0,0) for ( k, g) in money_ind]
    for u in range(0, len(givers)):
        v,w = money_ind[u]
        giver = givers[u]
        if( w >= 0 and w <=len(dict_of_members)):
            individual_sum = auxiliary[u][0] 
            remainder_sum = auxiliary[u][1]
            dict_of_members = { r:(int(val-v+remainder_sum) if r == giver else val) for r,val in dict_of_members.items()}
            if v>=0:
                indices_receivers = [indices_partition[u]+x for x in range(1,w+1)]
                receivers = [dict_of_lines[i][0] for i in indices_receivers]
                dict_of_members = {r:(int(val+individual_sum) if r in receivers else val) for r,val in dict_of_members.items()}
    return dict_of_members


def main():
   input_file = "gift1.in"
   output_file= "gift1.out"
   dict_lines = generate_dico_from_file(input_file)
   dict_members = initialize_money(dict_lines)    
   dict_members_updated = compute_sum_money(dict_lines, dict_members)
   write_output_file(output_file, dict_members_updated)
 
################################### CALLING MAIN FUNCTION ###########################################################   
main()
