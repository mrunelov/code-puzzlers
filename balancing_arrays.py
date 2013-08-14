# -*- coding: utf-8 -*-

""" 
@author: Martin Runelöv

Thursday Code Puzzler: Balancing Arrays
http://java.dzone.com/articles/thursday-code-puzzler-12

Given an array of numbers,  
return the index at which the array can be balanced by all numbers on the 
left side add up the the sum of all numbers of the right side. 
If no such index exists, return -1.

For example, 
an array with [1,5,6,7,9,10] can be balanced by splitting the array at position 4. 

"""

array = [1,5,6,7,9,10]

def balanced_index(array):
"""
Uses a generator since only one possible answer is possible. Defaults to -1.

"""	
	return next((i for i,_ in enumerate(array) if sum(array[:i]) == sum(array[i:])),-1)

print('Balanced at index ' + str(balanced_index(array)))