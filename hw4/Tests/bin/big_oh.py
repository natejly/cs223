#!/usr/bin/python3

import sys
import math

if __name__ == '__main__':
    usage = "USAGE: %s {-linear | -log | -loglinear | -quadratic | -constant | -polynomial=k | -polylog=k } bound n1 ..." % sys.argv[0];
    if len(sys.argv) < 3 or (sys.argv[2] == "-message" and len(sys.argv) < 5):
        print(usage)
        sys.exit(1)

    try:
        args = sys.argv[:]

        if args[1] == "-message":
            message = "FAIL " + args[2]
            del args[1:3]
        else:
            message = "FAIL"
            
        function = args[1]
        bound = float(args[2])
        start_n = 3
        if args[1] == "-linear":
            fxn = lambda x: x
        elif args[1] == "-log":
            fxn = lambda x : math.log(x, 2)
        elif args[1] == "-loglinear":
            fxn = lambda x : math.log(x, 2) * x
        elif args[1] == "-quadratic":
            fxn = lambda x : x * x
        elif args[1] == "-constant":
            fxn = lambda x : 1
        elif args[1].find("-polynomial") == 0:
            if len(args) < 3 or args[1].find("=") == -1:
                print(usage)
                sys.exit(1)
            exponent = float(args[1][args[1].find("=") + 1:])
            function = "%s" % (function)
            bound = float(args[2])
            start_n = 3
            fxn = lambda x : x ** exponent
        elif args[1].find("-polylog") == 0:
            if len(args) < 3 or args[1].find("=") == -1:
                print(usage)
                sys.exit(1)
            exponent = float(args[1][args[1].find("=") + 1:])
            function = "%s" % (function)
            bound = float(args[2])
            start_n = 3
            fxn = lambda x : math.log(x) ** exponent
        else:
            print(usage)
            sys.exit(1)

        ns = []
        for n in args[start_n:]:
            ns.append(int(n))
            
    except ValueError as e:
        print(e)
        print(usage)
        sys.exit(1)

    try:
        failures = 0
        for n in ns:
            off = int(input())
            on = int(input())
            diff = on - off
            quotient = diff / fxn(n)
            if quotient > bound:
                failures = failures + 1
                print("%s: %s %d %d %f>%f" % (message, function, n, diff, quotient, bound))
        if failures == 0:
            print("PASS")
    except ValueError:
        print("%s: numnumeric value in standard input" % args[0])


