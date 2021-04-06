# PT:SD Lua ECS


## EntityManager
EntityManager se encarga de recibir el input y el deltaTime y pasárselo a las entidades.

Para registrar una entidad basta con llamar a `addEntity(entity)` del manager y se encarga de registarla en los sistemas debidos



### Credit where credit is due

Basado mucho en [lovetoys](https://github.com/lovetoys/lovetoys), libreria ECS de Lua 