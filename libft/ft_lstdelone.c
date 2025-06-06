/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:28:18 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:47:22 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

// #include <stdio.h>

// // contentを解放するための関数
// void	del_content(void *content)
// {
// 	free(content); // メモリを解放
// }

// int	main(void)
// {
// 	t_list	*node;

// 	// ノードを作成して内容を動的に割り当てる
// 	node = ft_lstnew(malloc(20));
// 	if (node == NULL || node->content == NULL)
// 	{
// 		printf("Failed to allocate memory\n");
// 		return (1);
// 	}
// 	// ノードの内容に文字列を設定
// 	snprintf(node->content, 20, "Test Node");
// 	// ノードの内容を表示
// 	printf("Before deletion: %s\n", (char *)node->content);
// 	// ノードを削除（内容とノード自体の解放）
// 	ft_lstdelone(node, del_content);
// 	// ノードが削除されたことを確認（削除後にアクセスしないよう注意）
// 	printf("Node deleted\n");
// 	return (0);
// }
