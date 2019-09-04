# -*- coding: utf-8 -*-
"""
Created on Tue Sep  3 10:48:42 2019

@author: HTT 
@task: training 
"""

''' GOOGLE CHALLENGE : Find the longest word in a dictionary that is a subsequence of a given string'''

def dictString(word):
    dict = {}
    for index, w in enumerate(word):
        if(w in dict):
            dict[w].append(index)
        else:
            dict[w] = []
            dict[w].append(index)
    return dict   

  
def subsequenceFound(liste1):
    if not liste1:
        return False
    for i in range(0,len(liste1)-1):
        if not (liste1[i] < liste1[i+1]):
            return False
    return True

def weaveLists(mylist1, mylist2,prefix,bigList):
    if ( not mylist1 or not mylist2):
        newList = prefix.copy()
        newList.extend(mylist1)
        newList.extend(mylist2)
        bigList.append(newList)
        return       
    
    headFirst = mylist1[0]
    mylist1.remove(mylist1[0])
    r = len(prefix)   
    prefix.insert(r, headFirst)
    weaveLists(mylist1, mylist2, prefix, bigList)
    prefix.remove(prefix[r])
    mylist1.insert(0,headFirst)    
    headSecond = mylist2[0]
    mylist2.remove(headSecond)
    r = len(prefix)
    prefix.insert(r, headSecond)
    weaveLists(mylist1, mylist2, prefix, bigList)
    prefix.remove(prefix[r])
    mylist2.insert(0,headSecond)
     
def maximumLength(l):
    if not l:
        return
    max =-1;
    for i in range(0, len(l)-1):
        print( len(l[i]))
        if ( len(l[i]) > max):
            max = len(l[i])
    return max
        
def findLargerNumber(last, myList):
    if not myList:
        return False
    ll = sorted(myList)
    r = len(myList)
    if (ll[r-1]<=last):
        return False
    for u in ll:
        if ( u > last):
            last = u
            return True
    return False   
    
def buildValuesWords(one_word, given_word, all_words_dict):
     if (not one_word or not given_word):
        return
     big_dict = dictString(given_word)
     last =-1
     
     for i in range(0,len(one_word)-1):
        if (given_word.count(one_word[i]) == 0) :
            all_words_dict[one_word] = -1
            return        
        else:
            l1 = big_dict[one_word[i]]       
            if not (findLargerNumber(last, l1) == True):
                all_words_dict[one_word] = -1
                return        
     all_words_dict[one_word] = len(one_word)         
     
     
def findLongestSubsequence(given_word,all_words_dict):
    for w in all_words_dict.keys():
        buildValuesWords(w, given_word,all_words_dict)
    values_sorted = sorted(all_words_dict.values())
    r = len(values_sorted)    
    max = values_sorted[r-1]
    print ( max)
    subsequence = [key for (key, value) in all_words_dict.items() if value == max]
    print ( subsequence[0])
    return subsequence[0]
    
the_given_word ="ABPPPLEE"
the_dict = {"ABLE":0, "ALE":0,"APPLE":0,"BALE":0,"KANGAROO":0}
the_subsequence = findLongestSubsequence(the_given_word,the_dict)   
    
    
    
    
    
    
    

    
    