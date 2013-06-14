# Fast math version:

def sum_of_multiples(i, c):
    return i*((c/i)*(c/i+1))/2

def total_sum_of_multiples(x,y,c):
    return (sum_of_multiples(x,999) +
            sum_of_multiples(y,999) -
            sum_of_multiples(x*y,999))

print total_sum_of_multiples(3,5,999)
