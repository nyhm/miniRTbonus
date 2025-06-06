/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:21:08 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:22:42 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*last;
// 	t_list	*current;
// 	t_list	*temp;

// 	// リストの先頭をNULLで初期化
// 	head = NULL;
// 	// ノードを作成してリストに追加
// 	head = ft_lstnew("Node 1");
// 	head->next = ft_lstnew("Node 2");
// 	head->next->next = ft_lstnew("Node 3");
// 	// リストの最後のノードを取得
// 	last = ft_lstlast(head);
// 	if (last != NULL)
// 		// 最後のノードの内容を表示
// 		printf("Last node content: %s\n", (char *)last->content);
// 	else
// 		// リストが空の場合のメッセージ
// 		printf("List is empty.\n");
// 	// メモリを解放
// 	current = head;
// 	while (current != NULL)
// 	{
// 		temp = current;
// 		current = current->next;
// 		free(temp);
// 	}
// 	return (0);
// }
