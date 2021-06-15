from Functions import StepFunction

sf = StepFunction([[3, 2, 1]])

sf.push(1, 2, 3)
sf.print()
sf.derivative().print()
sf.integral().print()
print(f"{sf(5) = }")
print(sf + sf.derivative())
print(sf * 5- sf.derivative())