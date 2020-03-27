import pandas as pd
import os

directory = "data"
inputFile = "Articles.csv"
outputFile = "Articles-prep.csv"

data = pd.read_csv(os.path.join(directory, inputFile), encoding="latin")

newData = data[['Heading', "Article"]]

newData.to_csv(os.path.join(directory, outputFile), index=False)
print("Done")
