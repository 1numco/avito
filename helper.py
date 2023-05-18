import os
import re

with open("text_files/russian_input.txt", "r") as f:
    content = f.read()
    cleaned_content = re.sub(r'[^a-zA-Z]+', ' ', content)
    lowercased_cleaned_content = cleaned_content.lower()
    
    words = lowercased_cleaned_content.split(' ')
    freq = {}
    for word in words:
        if word:
            if word in freq:
                freq[word] += 1
            else:
                freq[word] = 1
    sorted_items = sorted(freq.items(), key=lambda x: (-x[1], x[0]))
    with open("text_files/russian_etalon_output.txt", "w") as f1:
        content = ""
        for item in sorted_items:
            content += str(item[1]) + " " + item[0] + '\n'
        content = content
        f1.write(content)