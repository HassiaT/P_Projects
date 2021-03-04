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

''' Given a string find the first non-repeating character in it and return its index. If it doesn't exist '''
''' return -1 '''
def find_index_first_non_repeating_char(s):
    index = -1
    count_characters = {}
    current = -1
    for c in s:
     if not c in count_characters:
         count_characters[c] = 1
     else:
         count_characters[c] += 1
    for c in s:
        current += 1
        if (count_characters[c] == 1):
            index = current
            break
    return index

'''
def main():
    s="abcbdbrirol"
    s_bis="abcdefg"
    print(checking_str_duplicate(s_bis))

   
if __name__ == "__main__":
    main()

'''


    