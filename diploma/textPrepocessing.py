import string

import time
from textblob import TextBlob
import re
import nltk
from contractions import contractions_dict


# removing punctuation

workData = text.translate(str.maketrans('','',string.punctuation))

#to lower case
workData = workData.lower()

#contractions


def expand_contractions(text, contractions_dict):
    contractions_pattern = re.compile('({})'.format('|'.join(contractions_dict.keys())),
                                      flags=re.IGNORECASE | re.DOTALL)
def expand_match(contraction):
        match = contraction.group(0)
        first_char = match[0]
        expanded_contraction = contractions_dict.get(match) \
            if contractions_dict.get(match) \
            else contractions_dict.get(match.lower())
        expanded_contraction = expanded_contraction
        return expanded_contraction
expanded_text = contractions_pattern.sub(expand_match, text)
    expanded_text = re.sub("'", "", expanded_text)
    return expanded_text



# removing stop words
# from nltk.corpus import stopwords
#     set(stopwords.words('english'))
# from nltk.tokenize import word_tokenize