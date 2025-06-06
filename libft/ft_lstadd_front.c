/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:12:06 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:17:56 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	// リストの初期化
// 	t_list *head = NULL;

// 	// ノードを作成
// 	t_list *node1 = ft_lstnew("First Node");
// 	t_list *node2 = ft_lstnew("Second Node");

// 	// ノードをリストに追加
// 	ft_lstadd_front(&head, node1);
// 	ft_lstadd_front(&head, node2); // node2を先頭に追加

// 	// リストの内容を表示
// 	t_list *current = head;
// 	while (current != NULL)
// 	{
// 		printf("Node content: %s\n", (char *)current->content);
// 		current = current->next;
// 	}

// 	// メモリを解放
// 	current = head;
// 	while (current != NULL)
// 	{
// 		t_list *temp = current;
// 		current = current->next;
// 		free(temp);
// 	}

// 	return (0);
// }