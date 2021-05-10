# library & dataset
import matplotlib
matplotlib.use('Agg')

import seaborn as sns
df = sns.load_dataset('iris')



# use the function regplot to make a scatterplot
sns.regplot(x=df["sepal_length"], y=df["sepal_width"])

import matplotlib.pyplot as plt
plt.show()

