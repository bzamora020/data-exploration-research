# library & dataset
import seaborn as sns
import pandas as pd

states = pd.read_csv('numShootings.csv')
df = sns.load_dataset('numShootings.csv')
import matplotlib.pyplot as plt

# Basic correlogram
sns.pairplot(data = df, hue = "State")
sns.plt.show()
