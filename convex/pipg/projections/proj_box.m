function xproj = proj_box(x, l, u)
        xproj = min(max(x, l), u);
end