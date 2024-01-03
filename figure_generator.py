import csv
import os
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
from matplotlib.ticker import ScalarFormatter


# This will be your new function to set up the graph for a subplot
def setup_subplot(ax, x_exponential, y_exponential, x_lim=None, y_lim=None):
    ax.ticklabel_format(style='plain')
    x_label = f"($10^{x_exponential}$)" if x_exponential else ""
    ax.set_xlabel(f"Array Length {x_label}")
    ax.set_ylabel(f"Computations (Log Scale)")  # ($10^{y_exponential}$)")
    if x_lim is not None:
        ax.set_xlim(x_lim)
    if y_lim is not None:
        ax.set_ylim(y_lim)


def generate_subplot_figure(ax, csv_file, x_exponential, y_exponential, x_lim, y_lim, linestyles=None, colors=None):
    x_arr, sort_col_list, headers = parse_csv(csv_file)
    if linestyles is None:
        linestyles = ['-'] * len(headers)
    if colors is None:
        colors = [f"C{i}" for i in range(len(headers))]
    x_arr = [v / (1 * 10 ** x_exponential) for v in x_arr]
    for i in range(1, len(headers)):
        # y_arr = [np.log(v / (1 * 10 ** y_exponential)) for v in sort_col_list[i]]
        y_arr = [np.log(v) for v in sort_col_list[i]]
        ax.plot(x_arr, y_arr, label=headers[i], linestyle=linestyles[i-1], color=colors[i - 1])
    setup_subplot(ax, x_exponential, y_exponential, x_lim, y_lim)


def generate_bar_plot(ax, csv_file, colors):
    x_arr, sort_col_list, headers = parse_csv(csv_file)

    y_values = [y_arr[-1] for y_arr in sort_col_list]
    # Check if the number of colors matches the number of headers

    ax.set_xticklabels(headers[1:], rotation=45, ha='center')  # 'ha' is short for horizontalalignment

    # Plotting the bar graph on the given ax object with the provided colors
    ax.bar(headers[1:], y_values[1:], color=colors)



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
    line_styles = ["-", "-", "-", "-", "-"]
    generate_subplot_figure(ax1, "fig_5.csv", 3, 9, None, None, line_styles)
    generate_subplot_figure(ax2, "fig_new.csv", 3, 9, None, None, line_styles)
    generate_subplot_figure(ax3, "fig_6.csv", 3, 9, None, None, line_styles)
    generate_subplot_figure(ax4, "fig_7.csv", 3, 9, None, None, line_styles)

    line_styles = ["-"] * 5

    generate_subplot_figure(ax5, "fig_8.csv", 0, 9, None, None, line_styles[-2:], colors=["C3", "C4"])

    line_styles = ["-"] * 5
    colors = ["C4"] + [f"C{i}" for i in range(4)]
    '''
    generate_bar_plot(ax6, "fig_9-10a.csv", colors)
    generate_bar_plot(ax7, "fig_9-10b.csv", colors)
    generate_bar_plot(ax8, "fig_9-10c.csv", colors)
    generate_bar_plot(ax9, "fig_9-10d.csv", colors)
    '''
    generate_subplot_figure(ax6, "fig_9-10a.csv", 3, 9, None, None, line_styles, colors)
    generate_subplot_figure(ax7, "fig_9-10b.csv", 3, 9, None, None, line_styles, colors)
    generate_subplot_figure(ax8, "fig_9-10c.csv", 3, 9, None, None, line_styles, colors)
    generate_subplot_figure(ax9, "fig_9-10d.csv", 3, 9, None, None, line_styles, colors)

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
    fig_5.savefig('figures_1_to_4_log.png', dpi=600)
    fig_6.savefig('figures_8_log.png', dpi=600)
    fig_7.savefig('figures_9-10_log.png', dpi=600)

    # Show figures
    fig_5.show()
    fig_6.show()
    fig_7.show()


if __name__ == '__main__':
    main()
