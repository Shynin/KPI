import requests
from bs4 import BeautifulSoup
import time
# from textblob import TextBlob
from lxml import html

# url = input("enter your url: ")
# url = 'https://www.theguardian.com/uk-news/2019/aug/16/police-officers-death-sparks-sweeping-inquiry'
url = 'https://www.bbc.com/news/business-49591793'
# url = 'https://www.dailymail.co.uk/news/article-7437087/Boris-Johnson-declares-war-against-John-Bercow-stands-Tory-candidate-against-him.html'

response = requests.get(url)
soup = BeautifulSoup(response.text, "html.parser")
#The Guardian
if "www.theguardian.com" in url:
    print("Guardian")
    quote = soup.find('div', class_='content__article-body')
    scraped = []
    article = soup.find('div', class_='content__article-body')
elif "www.bbc.com" in url:
    print("BBC")
    quote = soup.find('div', class_='story-body__inner')
    scraped = []
    article = soup.find('div', class_='story-body__inner')
elif "www.dailymail.co.uk" in url:
    print("DailyMail")
    quote = soup.find('div', class_='article-text')
    scraped = []
    article = soup.find('div', class_='article-text')
paragraphs = article.find_all('p')
for paragraph in paragraphs:
    scraped.append(paragraph.text)
text = ' '.join(scraped)

# print(text)

# cleaning data with uppercase, commas, dots AND STOP WORDS

# from nltk.corpus import stopwords
# stop_words = stopwords.words('english')
