d = {k: v for k, v in zip([1, 2, 3, 4], ["a", "b", "c", "d", "e", "fd"])}

for k,v in d.items():
    print(f"k = {k}, v = {v} ")


print(d)

print(d.get(52))