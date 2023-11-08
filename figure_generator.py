import matplotlib.pyplot as plt
import matplotlib as mpl
import os
import csv
from cycler import cycler
import matplotlib.ticker as ticker

from matplotlib.ticker import ScalarFormatter

markers = ['v', 's', "h", 'D', 'X', 'v', 's', "h", 'D', 'X']
colors = [
    "C0",
    "C1",
    "C3",
    "C5",
    "C4",
    "orangered",
    "#070600",
    "#23B5D3",
    "#700548",
]


# This will be your new function to set up the graph for a subplot
def setup_subplot(ax, x_exponential, y_exponential, x_lim=None, y_lim=None):
    ax.ticklabel_format(style='plain')
    x_label = f"($10^{x_exponential}$)" if x_exponential else ""
    ax.set_xlabel(f"Array Length {x_label}")
    ax.set_ylabel(f"Computations ($10^{y_exponential}$)")

    if x_lim is not None:
        ax.set_xlim(x_lim)

    if y_lim is not None:
        ax.set_ylim(y_lim)


def generate_subplot_figure(ax, csv_file, x_exponential, y_exponential, x_lim, y_lim, color_offset=0):
    x_arr, sort_col_list, headers = parse_csv(csv_file)
    x_arr = [v / (1 * 10 ** x_exponential) for v in x_arr]
    for i in range(1, len(headers)):
        y_arr = [v / (1 * 10 ** y_exponential) for v in sort_col_list[i]]
        ax.plot(x_arr, y_arr, label=headers[i], color=colors[i - 1 + color_offset]) #f"C{i - 1 + color_offset}")
    setup_subplot(ax, x_exponential, y_exponential, x_lim, y_lim)


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


def add_text_to_ax(ax, text, pos_x=0.05, pos_y=0.97):
    ax.text(pos_x, pos_y, text, ha='left', va='top', transform=ax.transAxes,
            fontsize=12, color='black',
            bbox=dict(facecolor='white', alpha=0.5, edgecolor='none', boxstyle='round,pad=0.1'))


def main() -> None:
    # Now you would set up the subplots and call your functions
    fig_5, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(14, 10))
    fig_6, ax5 = plt.subplots(1, 1, figsize=(14, 10))
    fig_7, ((ax6, ax7), (ax8, ax9)) = plt.subplots(2, 2, figsize=(14, 10))

    # You would call the appropriate figure generation function for each subplot
    generate_subplot_figure(ax1, "fig_5.csv", 3, 9, (0, 1000), (0, 180))
    generate_subplot_figure(ax2, "fig_new.csv", 3, 9, (0, 1000), (0, 180))
    generate_subplot_figure(ax3, "fig_6.csv", 3, 9, (0, 1000), (0, 180))
    generate_subplot_figure(ax4, "fig_7.csv", 3, 9, (0, 1000), (0, 180))
    generate_subplot_figure(ax5, "fig_8.csv", 0, 9, (0, 1500), (-1, 20), 3)

    generate_subplot_figure(ax6, "fig_9-10a.csv", 3, 9, (0, 1000), (0, 175), 4)
    generate_subplot_figure(ax7, "fig_9-10b.csv", 3, 9, (0, 1000), (0, 175), 4)
    generate_subplot_figure(ax8, "fig_9-10c.csv", 3, 9, (0, 1000), (0, 175), 4)
    generate_subplot_figure(ax9, "fig_9-10d.csv", 3, 9, (0, 1000), (0, 175), 4)

    ax1.set_title("A")
    ax2.set_title("B")
    ax3.set_title("C")
    ax4.set_title("D")

    ax6.set_title("A")
    ax7.set_title("B")
    ax8.set_title("C")
    ax9.set_title("D")

    add_text_to_ax(ax1, "k = 50,000")
    add_text_to_ax(ax2, "k = 500,000")
    add_text_to_ax(ax3, "k = 5,000,000")
    add_text_to_ax(ax4, "k = 50,000,000")
    add_text_to_ax(ax5, "k = 150,000,000")

    add_text_to_ax(ax6, "k = 50,000", .03)
    add_text_to_ax(ax7, "k = 500,000", .03)
    add_text_to_ax(ax8, "k = 5,000,000", .03)
    add_text_to_ax(ax9, "k = 50,000,000", .03)


    ax2.legend(loc='upper right')
    ax5.legend(loc='upper right')
    ax7.legend(loc='upper right')

    # Apply tight layout
    fig_5.tight_layout()
    fig_6.tight_layout()
    fig_7.tight_layout()

    # Save the entire figure
    fig_5.savefig('figures_1_to_4.png', dpi=600)
    fig_6.savefig('figures_8.png', dpi=600)
    fig_7.savefig('figures_9-10.png', dpi=600)

    # Show figures
    fig_5.show()
    fig_6.show()
    fig_7.show()

    '''
    generate_figure_5()
    generate_figure_6()
    generate_figure_7()
    generate_figure_8()
    #generate_figure_9()
    #generate_figure_10()'''


if __name__ == '__main__':
    main()
