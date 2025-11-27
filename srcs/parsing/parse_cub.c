/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:49:40 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/25 19:07:03 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void    parse_cub(char **tab, t_config *config)
// {
//     int i;

//     i = 0;
//     if (!tab[i])
//         print_error("error : no map found in .cub file");
//     while (tab[i] && !is_map_start(tab[i]))
//     {
//         if (!is_empty_line(tab[i]))
//             parse_config_line(tab[i], config);
//         i++;
//     }
//     check_all_elements_present(config); 
//     if (!tab[i])
//         print_error("error : map not found after configuration");
//     parse_map(&tab[i], config);
//     is_valid_map(config);
// }

void    parse_cub(char **tab, t_config *config)
{
    int i;

    i = 0;
    if (!tab[i])
        print_error("error : no map found in .cub file");
    
    printf("DEBUG: Indice i avant boucle de config : %d\n", i); // <-- 1. Ici
    
    while (tab[i] && !is_map_start(tab[i]))
    {
        if (!is_empty_line(tab[i]))
            parse_config_line(tab[i], config);
        i++;
    }
    
    printf("DEBUG: Indice i après boucle de config : %d\n", i); // <-- 2. Et ici
    
    check_all_elements_present(config); 
    if (!tab[i])
        print_error("error : map not found after configuration");
    parse_map(&tab[i], config);
    is_valid_map(config);
}

