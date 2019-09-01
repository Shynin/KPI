import requests
from bs4 import BeautifulSoup
import time
from textblob import TextBlob
from lxml import html

# url = input("enter your url: ")
url = 'https://www.theguardian.com/uk-news/2019/aug/16/police-officers-death-sparks-sweeping-inquiry'

response = requests.get(url)
soup = BeautifulSoup(response.text, "html.parser")
quote = soup.find('div', class_='content__article-body')
scraped = []
article = soup.find('div', class_='content__article-body')
paragraphs = article.find_all('p')
for paragraph in paragraphs:
    scraped.append(paragraph.text)
text = ' '.join(scraped)

# print(text)

# cleaning data with uppercase, commas, dots AND STOP WORDS

# from nltk.corpus import stopwords
# stop_words = stopwords.words('english')
