# -*- coding: utf-8 -*-
"""
ID: hassia.1
LANG : PYTHON3
TASK : friday
"""

def compute_next_date(l, M):
    if ( not l or l[2] > M ):
        return
    next_date= l.copy()
    if( l[0] == 13 and l[1]>= 1 and l[1]<=11):
        next_date[1] = l[1]+1
    elif l[1] == 12:
        next_date[1] = 1 
        next_date[2] = l[2] +1
    next_date[0] = 13
    return next_date    
    
def initialize_number_of_days_per_month():
    months = list(range(1,13))
    n_days = [31]*12
    dict_days = dict(zip(months, n_days))
    liste_30 = [4,6,9,11] #April, June, September, November
    dict_days = { r:(30 if r in liste_30 else 28 if r== 2 else val) for r, val in dict_days.items()}  
    return dict_days
   
def building_thirteen_dates(start_date, N):
    if start_date:
        all_dates= []
        #start_date = [1,1,1900] # 01 January 1900
        end_year = int(start_date[2]) + int(N) -1
        current_date = start_date.copy()
        while(current_date[2] <= end_year):
            n_date = compute_next_date(current_date, end_year)
            if ( n_date[1] <= 12 and n_date[2] <= end_year) :
                all_dates.append(n_date) 
            current_date = n_date
    return all_dates
    

def initialize_frequency():
    days = ["MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY","SUNDAY"]
    id_days= list(range(0,7))
    mapping_days= dict(zip(days,id_days))
    return mapping_days  

def is_a_leap_year(year):
    if year%100 == 0 and year%400 ==0:
        return True
    elif (not(year%100==0)) and year%4 ==0:
        return True
    return False


def update_days_february(dictio, year):
    if dictio:
        if is_a_leap_year(year):
            dictio[2] = 29 #february has 29 days in a leap year
    return dictio


def days_elapsed(l_current, l_previous, d):
    resultat =0
    if l_current and l_previous:
      #update dictionary d accordingly
      d = update_days_february(d, l_current[2])     
      if ( l_current[1] != l_previous[1]):
        prev_day = l_previous[0] #day
        prev_month_id = l_previous[1] #month
        n_days_previous = d[prev_month_id]
        resultat += int(n_days_previous - prev_day+ l_current[0])
      else:
        resultat += int(l_current[0]-l_previous[0])
    return resultat

def get_key(dico, value):
    if dico :
        for a,b in dico.items():
            if (b == value):
                return a
    return None   
    
def compute_frequence(N, starting_point):
    if starting_point and N>0 and N<= 400 :
        map_days = initialize_frequency()
        all_the_dates = building_thirteen_dates(starting_point, N)
        dict_days = initialize_number_of_days_per_month()
        last_day =["MONDAY"]
        elapsed_tail = []
        last_date = starting_point
        for i in range(0, len(all_the_dates)):
            r = days_elapsed(all_the_dates[i], last_date, dict_days)
            last_index = len(last_day)-1
            id_last_day = (map_days[last_day[last_index]] + r) %7
            last_day_name = get_key(map_days, id_last_day) 
            last_day.append(last_day_name)
            last_date = all_the_dates[i]
            dict_days = { r:(28 if r == 2 else val) for r, val in dict_days.items()}
            elapsed_tail.append(last_day_name)
        days = ["SATURDAY","SUNDAY", "MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY"]
        id_days= [0]*7
        final_dictionary = dict(zip(days,id_days))
        for k in final_dictionary.keys():
            final_dictionary[k] = elapsed_tail.count(k)
    return final_dictionary

    
def main():
    starting_date = [1,1,1900]
    input_file = "friday.in"
    output_file="friday.out"
    with open(input_file, "r") as fih:
        line = fih.readline()
        number_of_years = int(line)
        if number_of_years>0 and number_of_years<=400:
            frequencies = compute_frequence(number_of_years, starting_date)
            with open(output_file,"w") as f_out:
                all_values = list(frequencies.values())
                for i in range(0, len(all_values)):
                    if not i==len(all_values)-1:                    
                        f_out.write("".join([str(all_values[i]), ' ']))                
                    else:
                        f_out.write("".join([str(all_values[i]), '\n']))                
                f_out.close()
    fih.close()   
     

       
#############################################################################☻ CALLING MAIN FUNCTION ########################################################
main()