function sig = power_iteration(H, Ht, opts)
    z = ones(size(H,2),1);
    z = z / norm(z);
    sig = 0;
    sig_old = 1e6;
    iter = 1;
    while (abs(sig-sig_old) >= opts.eps_abs_pow + opts.eps_rel_pow*max(sig, sig_old) && iter < opts.max_iter_pow)
        sig_old = sig;
        z = Ht*H*z;
        sig = norm(z);
        z = z / sig;
        iter = iter + 1;
    end
    sig = sig * (1 + opts.eps_buff);
end