from siteParser import text
import string
import nltk
import re
from nltk.corpus import stopwords
# from nltk. import stopwords


# to lower case
workData = text.lower()

# removing punctuation with translate
workData = workData.translate(str.maketrans('', '', string.punctuation))

# removing punctuation with regex
# workData = re.sub(r"[,“–”)(@\'?\.:$%_]", "", text)


# removing stop words
stop_words = set(stopwords.words('english'))
workData = ' '.join(
    [word for word in workData.split() if word not in stop_words])

print(workData)
# contractions


# print(workData)

# from textblob import TextBlob
# testimonial = TextBlob(workData)
# print(testimonial.sentiment)
# print(testimonial.sentiment.polarity)
