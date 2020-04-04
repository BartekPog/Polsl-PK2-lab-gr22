import pandas as pd
import csv
import os

directory = "data"
inputFile = "Articles.csv"
outputFile = "Articles-prep.csv"

data = pd.read_csv(os.path.join(directory, inputFile), encoding="latin")

newData = data[['Heading', "Article"]]


def fixText(text: str) -> str:
    partial = text.replace("strong>", "")
    partial = partial.replace("<strong", "")
    return partial.replace('"', "'")


newData["Article"] = newData["Article"].apply(
    func=fixText).str.strip()

newData["Heading"] = newData["Heading"].apply(
    func=fixText).str.strip()


newData.to_csv(os.path.join(directory, outputFile), index=False,
               header=False, quoting=csv.QUOTE_NONNUMERIC)
print("Done")
