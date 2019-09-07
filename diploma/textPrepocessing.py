from siteParser import text
import string
import nltk
import re
from nltk.corpus import stopwords

# removing punctuation with translate
# workData = text.translate(str.maketrans('','',string.punctuation))
# removing punctuation with regex
workData = re.sub(r"[,“–”)(@\'?\.:$%_]", "", text)

#to lower case
workData = workData.lower()
#contractions


#removing stop words
stop_words = set(stopwords.words('english'))
workData = ' '.join([word for word in workData.split() if word not in stop_words])

print(workData)

from textblob import TextBlob
testimonial = TextBlob(workData)
print(testimonial.sentiment)
print(testimonial.sentiment.polarity)
