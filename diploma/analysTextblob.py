from textblob import TextBlob
from textPrepocessing import workData
from siteParser import text

print(text)


# TextBlob
testimonial = TextBlob(workData)
print("Text Blob")
print(testimonial.sentiment)
print(testimonial.sentiment.polarity)

# paralleldots
# import paralleldots
# paralleldots.set_api_key('API KEY')
# paralleldots.get_api_key()
# print("Parallel Dots")
# print(paralleldots.sentiment(workData))
