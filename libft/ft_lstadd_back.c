/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:23:43 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:27:11 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	t_list	*current;
// 	t_list	*temp;

// 	// リストの先頭をNULLで初期化
// 	head = NULL;
// 	// ノードを作成
// 	node1 = ft_lstnew("Node 1");
// 	node2 = ft_lstnew("Node 2");
// 	node3 = ft_lstnew("Node 3");
// 	// ノードをリストの末尾に追加
// 	ft_lstadd_back(&head, node1); // headが空の場合、node1を追加
// 	ft_lstadd_back(&head, node2); // node2を追加
// 	ft_lstadd_back(&head, node3); // node3を追加
// 	// リストを表示
// 	current = head;
// 	while (current != NULL)
// 	{
// 		printf("Node content: %s\n", (char *)current->content);
// 		current = current->next; // 次のノードに移動
// 	}
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
