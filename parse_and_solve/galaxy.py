def calculate(expression):
    expression.split()
    if expression[0] == "S":
        return calculate(next line)
    elif expression[0] == "expr":
        if expression[1] == "term":
            return calculate(next line)
        elif expression[1] == "-":
            return calculate(next) - calculate(after)
        elif expression[1] == "+":
            return calculate(next) + calculate(after)
        elif expression[1] == "div":
            return calculate(next) / calculate(after)
        elif expression[1] == "forward_slash":
            return calculate(next) / calculate(after)
        elif expression[1] == "times":
            return calculate(next) * calculate(after)
        elif expression[1] == "=":
            return calculate(next) == calculate(after)
        elif expression[1] == "lt":
            return calculate(next) < calculate(after)
        elif expression[1] == "leq":
            return calculate(next) <= calculate(after)
        elif expression[1] == "gt":
            return calculate(next) - calculate(after)
        elif expression[1] == "geq":
            return calculate(next) - calculate(after)
        elif expression[1] == "neq":
            return calculate(next) != calculate(after)
        #Sum lim etc
    elif expression[1] != "(expr)":
        return expression[1]
    
    else:
        return calculate(next)
        
        
        
        
