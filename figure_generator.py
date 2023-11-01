import matplotlib.pyplot as plt
import matplotlib as mpl
import os
import csv
from cycler import cycler
mpl.rcParams['axes.spines.top'] = False
mpl.rcParams['axes.spines.right'] = False


def show_graph(output_file):
    plt.legend()
    plt.ticklabel_format(style='plain')
    plt.title("Sorting Algorithm Array Accesses and Comparisons")
    plt.xlabel("Array Length")
    plt.ylabel("Array Accesses + Comparisons (Billions)")
    plt.grid()
    plt.rcParams['savefig.dpi'] = 600
    mpl.rcParams['axes.spines.top'] = False
    mpl.rcParams['axes.spines.right'] = False
    plt.tight_layout()
    plt.savefig(output_file)
    plt.show()


def parse_csv(filename):
    with open(filename, 'r') as f:

        lines = f.readlines()
        headers = lines[0].strip().split(",")
        sort_col_list = [[] for _ in range(len(headers))]

        for row in range(1, len(lines)):
            line = lines[row].strip().split(",")
            for col in range(len(line)):
                sort_col_list[col].append(float(line[col]))

        return sort_col_list[0], sort_col_list, headers


def generate_figure_5():
    x_arr, sort_col_list, headers = parse_csv("fig_5.csv")

    markers = ['v', 's', 'h', 'D', 'X']
    for i in range(1, len(headers)):
        plt.plot(x_arr[::10], [v / 1000000000 for v in sort_col_list[i][::10]], markers[i - 1] + "-", label=headers[i])

    show_graph("figure_5.png")


def generate_figure_6():
    x_arr, sort_col_list, headers = parse_csv("fig_6.csv")

    markers = ['v', 's', "h", 'D', 'X']
    for i in range(1, len(headers)):
        plt.plot(x_arr[::10], [v / 1000000000 for v in sort_col_list[i][::10]], markers[i - 1] + "-", label=headers[i])

    show_graph("figure_6.png")


def generate_figure_7():
    x_arr, sort_col_list, headers = parse_csv("fig_7.csv")

    markers = ['v', 's']
    for i in range(1, len(headers)):
        plt.plot(x_arr[::500], [v / 1000000000 for v in sort_col_list[i][::500]], markers[i - 1] + "-", label=headers[i])
    show_graph("figure_7.png")


def generate_figure_8():
    x_arr, sort_col_list, headers = parse_csv("fig_8.csv")

    markers = ['v', 's']
    for i in range(1, len(headers)):
        plt.plot(x_arr[::10], sort_col_list[i][::10], markers[i - 1] + "-", label=headers[i])

    show_graph("figure_8.png")

def main() -> None:
    generate_figure_5()
    generate_figure_6()
    generate_figure_7()
    generate_figure_8()


if __name__ == '__main__':
    main()
