import pandas as p
import matplotlib.pyplot as plt

if __name__ == "__main__":

    #load data set
    data = p.read_csv('data.csv')
    print("*----Information----*")
    print(data.info())
    print("*----Information----*")
    print("*-----Headers-----*")
    print(data.head()) #print the 5 first line
    print("*-----Headers-----*")

    def analyse_col(df, col, title, style):
        print(f"\n*-----{title}-----*")
        counts = df[col].value_counts()
        print(counts)
        print(counts / counts.sum() *100)#fréquence style
        print(df[col].unique())

        counts.sort_values(ascending=True).plot(kind=style)
        plt.title(title)
        plt.xlabel(col)
        plt.ylabel('Count')
        plt.tight_layout()
        plt.show()

        top_values = counts.idxmax()
        print(f"Top {col}: {top_values}")
        print(f"Insight: Les fans de {top_values} représentent {counts.max() / counts.sum() * 100:.1f}% du total.")

    print("\n------------------------------------\n")
    analyse_col(data, "style", "Preferred style", "bar")
    print("\n------------------------------------\n")
    analyse_col(data, "sport", "Preferred sport", "bar")

    #insight
    #style par sport
    print("\n------------------------------------\n")
    pivot = data.pivot_table(index="sport", columns="style", aggfunc="size", fill_value=0)
    print(pivot)
    pivot.plot(kind='bar', stacked=True)
    plt.title("Style preference per sport")
    plt.show()
    print("\n------------------------------------\n")
    #budget moyen

    budget_mean = data.groupby("style")["budget"].mean()
    print(budget_mean)
    most_expensive = budget_mean.idxmax()
    print(f"Insight: Le style le plus cher en moyenne est {most_expensive}.")
    print("\n------------------------------------\n")
    #style / genre
    gender_style = data.groupby(["gender", "style"]).size()
    print(gender_style)
    print("\n------------------------------------\n")
    #top 3 combo
    combo = data.groupby(["style", "color"]).size().sort_values(ascending=False).head(3)
    print(combo)
    print("\n------------------------------------\n")
    #budget / style
    cor = data[["budget"]].corr()
    print(cor)
    print("\n------------------------------------\n")