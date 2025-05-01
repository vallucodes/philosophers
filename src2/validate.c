/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:41:06 by vlopatin          #+#    #+#             */
/*   Updated: 2025/02/26 12:43:35 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>


void exit_error(int error_code);

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	validate_input(char **av)
{
	int	i;
	int	j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				exit_error(1);
		}
	}
}

// Assuming these are defined elsewhere
extern void validate_input(char **av);
extern int ft_isdigit(int c);

// Mock function for exit_error
void exit_error(int error_code) {
    printf("Exit called with error code: %d\n", error_code);
    exit(error_code);
}

int main() {
    // Test case 1: All valid digits
    char *test1[] = {"123", "456", "789", NULL};
    printf("Test 1: ");
    validate_input(test1);
    printf("Passed\n");

    // Test case 2: Contains a non-digit
    char *test2[] = {"123", "4a6", "789", NULL};
    printf("Test 2: ");
    validate_input(test2);
    printf("This should not be printed\n");

    // Test case 3: Empty string
    char *test3[] = {"123", "", "789", NULL};
    printf("Test 3: ");
    validate_input(test3);
    printf("Passed\n");

    // Test case 4: NULL array
    char *test4[] = {NULL};
    printf("Test 4: ");
    validate_input(test4);
    printf("Passed\n");

    return 0;
}
