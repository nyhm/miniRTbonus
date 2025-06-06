/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:31:52 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:47:13 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

// #include <stdio.h>

// // contentを解放するための関数
// void	del_content(void *content)
// {
// 	free(content); // メモリを解放
// }

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;

// 	// ノード1とノード2を作成
// 	node1 = ft_lstnew(malloc(20));
// 	node2 = ft_lstnew(malloc(20));
// 	if (node1 == NULL || node1->content == NULL || node2 == NULL
// 		|| node2->content == NULL)
// 	{
// 		printf("Failed to allocate memory\n");
// 		return (1);
// 	}
// 	// ノードの内容に文字列を設定
// 	snprintf(node1->content, 20, "First Node");
// 	snprintf(node2->content, 20, "Second Node");
// 	// ノードを連結
// 	node1->next = node2;
// 	// リストの内容を表示
// 	printf("Before clear:\n");
// 	printf("Node 1 content: %s\n", (char *)node1->content);
// 	printf("Node 2 content: %s\n", (char *)node2->content);
// 	// リストを削除（内容とノード自体の解放）
// 	ft_lstclear(&node1, del_content);
// 	// リストがクリアされたことを確認（クリア後にアクセスしないよう注意）
// 	if (node1 == NULL)
// 		printf("List cleared and set to NULL\n");
// 	return (0);
// }
