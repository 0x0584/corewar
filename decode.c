/*
l2:
        sti r1, %:live, %1
        and r1, %0, r1
live:
        live %1
        zjmp %:live
*/


bool errstr(enum e_errors err, bool ret) {
    ft_dprintf(2, "%s: %s\n", __func__, g_errstr[err]);
    return ret;
}

static inline bool has_three_args(t_u8 enc) {
    return enc & 0b11 && enc & 0b1100 && enc & 0b110000;
}

bool op_sti(t_player *p, union u_arg args[MAX_ARGS_NUMBER], t_u8 enc) {
    ft_dprintf(2, "executing %s\n", __func__);
    if (!has_three_args(enc))
        return errstr(invalid_arguments, false);

	bool ret = false;
	t_reg *r = &p->reg[args[0].u32];

    return (p->carry = ret);
}

op_t read_op(t_addr pc) { t_u8 op = *pc; }

int main(int argc, char *argv[]) {
    t_u8 file[] = {0x0b, 0x68, 0x01, 0x00, 0x0f, 0x00, 0x01, 0x06,
                   0x64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
                   0x00, 0x00, 0x00, 0x01, 0x09, 0xff, 0xfb};

    return 0;
}
