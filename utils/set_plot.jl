function set_fonts()::Nothing
    # Set the figure fonts.
    fig_smaller_sz = 13
    fig_small_sz = 19
    fig_med_sz = 15
    fig_big_sz = 22
    plt.rc("text", usetex=true)
    plt.rc("font", size=fig_small_sz, family="serif")
    plt.rc("axes", titlesize=fig_small_sz)
    plt.rc("axes", labelsize=fig_small_sz)
    plt.rc("xtick", labelsize=fig_smaller_sz)
    plt.rc("ytick", labelsize=fig_smaller_sz)
    plt.rc("legend", fontsize=fig_smaller_sz)
    plt.rc("figure", titlesize=fig_big_sz)
    plt.rc("figure", dpi=150) 
    plt.rc("figure", figsize = [7, 5])
    plt.rc("axes", xmargin=0)
    plt.rc("animation", html="html5")
    return nothing
end