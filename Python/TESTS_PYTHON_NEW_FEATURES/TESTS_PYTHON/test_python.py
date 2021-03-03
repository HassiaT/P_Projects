# -*- coding: utf-8 -*-
"""
Created on Wed Mar  3 13:40:04 2021

@author: THSMCODING
"""

''' PYTHON version 3.9.1 '''

''' Determine if a string has all unique characters ==> no duplicate characters '''
''' Return 0 if there are duplicates or the string is empty ''' 
''' otherwise return 1 ==> no repeated characters '''

def checking_str_duplicate(s):
    if not s:
        return 0;
    set_characters = set(s)
    print(set_characters)
    result = (len(set_characters) == len(s))
    return result
    
def main():
    s="abcbdbrirol"
    s_bis="abcdefg"
    print(checking_str_duplicate(s_bis))
    
    
if __name__ == "__main__":
    main()




    