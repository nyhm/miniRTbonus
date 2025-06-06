/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:18:31 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:21:05 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// リストの初期化
// 	t_list *head = NULL;

// 	// ノードを作成
// 	head = ft_lstnew("Node 1");
// 	head->next = ft_lstnew("Node 2");
// 	head->next->next = ft_lstnew("Node 3");

// 	// リストのサイズを取得
// 	int size = ft_lstsize(head);
// 	printf("List size: %d\n", size); // 期待される出力は 3

// 	// メモリを解放
// 	t_list *current = head;
// 	while (current != NULL)
// 	{
// 		t_list *temp = current;
// 		current = current->next;
// 		free(temp);
// 	}

// 	return (0);
// }