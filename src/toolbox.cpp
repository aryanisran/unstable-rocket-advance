namespace toolbox
{
    int map_int_to_range(int t, int t_range_min, int t_range_max, int range_min, int range_max)
    {
        return range_min + (((range_max - range_min)/(t_range_max - t_range_min) * (t - t_range_min)));
    }
}